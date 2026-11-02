/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:11:14 by vvalenti          #+#    #+#             */
/*   Updated: 2026/04/07 14:55:35 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerManager.hpp"

/* ************************************************************************** */
/*                                  Colors                                    */
/* ************************************************************************** */

static const RgbColor Green (0,200,0);
static const RgbColor Red   (200,0,0);
static const RgbColor Cyan  (0,255,244);

/* ************************************************************************** */
/*                                  Config                                    */
/* ************************************************************************** */


ServerManager::ServerManager(t_config config) : _config(config)
{
	_epoll_fd = epoll_create1(0);
	if (_epoll_fd < 0)
		throw std::runtime_error("epoll_create1 failed");

	for (size_t i = 0; i < config.servers.size(); i++)
	{
		Server server(config.servers[i]);

		_servers.push_back(server);
	}

	for (size_t i = 0; i < _servers.size(); i++)
	{
		int	server_fd = _servers[i].getFd();

		struct epoll_event	ev;
		ev.events = EPOLLIN;
		ev.data.fd = server_fd;

		if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) < 0)
			throw std::runtime_error("epoll_ctl failed");

		_serverFds.insert(server_fd);
		_fd_to_Server[server_fd] = &_servers[i];
	}
}


ServerManager::~ServerManager() {
	close(_epoll_fd);
	for (std::set<int>::iterator it = _serverFds.begin(); it != _serverFds.end(); it++)
	{
		close(*it);
	}
	for (std::set<int>::iterator it2 = _clientFds.begin(); it2 != _clientFds.end(); it2++)
	{
		close(*it2);
	}
}


/* ************************************************************************** */
/*                            Execution manager                               */
/* ************************************************************************** */

void ServerManager::tryParseRequest(Client &c)
{
	if (c.read_buffer.find("\r\n\r\n") == std::string::npos)
		return;

	Request req;

	if (!req.parse(c.read_buffer))
	{
		Server *server = _fd_to_Server[c.fd];
		std::string response = server->buildErrorResponse(400);

		c.write_buffer += response;
		enableWrite(c.fd);
		return;
	}
	c.should_close = (req.getHeader("Connection") == "close");

	Server *server = _fd_to_Server[c.fd];
	std::string response = server->handleRequest(req, c, *this);

	if (!response.empty())
	{
		c.write_buffer += response;
		enableWrite(c.fd);
	}
}

void ServerManager::run()
{
	struct epoll_event events[MAX_EVENTS];

	while (!g_stop)
	{
		int nfds = epoll_wait(_epoll_fd, events, MAX_EVENTS, 10);
		if (nfds < 0)
		{
			if (errno == EINTR)
				continue;
			throw std::runtime_error("epoll_wait failed");
		}

		for (int i = 0; i < nfds; i++)
		{
			int fd = events[i].data.fd;

			if (_serverFds.count(fd))
				handleNewConnection(fd);
			else if (_cgi_fd_to_client.count(fd))
				handleCgiEvent(fd);
			else
				handleClientEvent(fd, events[i].events);
		}

		checkCgiTimeouts();
	}
}

void ServerManager::handleClientEvent(int fd, uint32_t events)
{
	if (_clients.find(fd) == _clients.end())
		return ;
	Client &c = _clients[fd];

	if (events & EPOLLIN)
	{
		handleRead(c);
		if (_clients.find(fd) == _clients.end())
			return ;
	}

	if (events & EPOLLOUT)
	{
		handleWrite(c);
		if (_clients.find(fd) == _clients.end())
			return ;
	}
}


void ServerManager::handleNewConnection(int server_fd)
{
	while (true)
	{
		struct sockaddr_in addr;
		socklen_t len = sizeof(addr);

		int client_fd = accept(server_fd, (struct sockaddr *)&addr, &len);
		if (client_fd < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			perror("accept");
			break;
		}

		fcntl(client_fd, F_SETFL, O_NONBLOCK);

		struct epoll_event ev;
		ev.events = EPOLLIN;
		ev.data.fd = client_fd;

		if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) < 0)
		{
			close(client_fd);
			continue;
		}

		Client c;
		c.fd = client_fd;
		c.read_buffer.clear();
		c.write_buffer.clear();
		c.body_size = 0;
		Server *server = _fd_to_Server[server_fd];
		c.max_body_size = server->getMaxBodySize();
		c.state = Client::READING;
		c.should_close = false;
		c.headers_parsed = false;
		c.content_length = -1;

		_clients[client_fd] = c;

		_fd_to_Server[client_fd] = _fd_to_Server[server_fd];
		_clientFds.insert(client_fd);

		LOG(
			Cyan("[") << "INFO" << Cyan("] ") <<
			Green << "Client (" << RESET
			<< c.fd <<
			Green << ") connected." << RESET
		);
	}
}

void ServerManager::handleRead(Client &c)
{
	char buffer[4096];

	while (true)
	{
		ssize_t n = read(c.fd, buffer, sizeof(buffer));

		if (n > 0)
		{
			c.read_buffer.append(buffer, n);

			if (!c.headers_parsed)
			{
				size_t	pos = c.read_buffer.find("\r\n\r\n");
				if (pos != std::string::npos)
				{
					c.headers_parsed = true;
					Request tmp;
					std::string headers = c.read_buffer.substr(0, pos + 4);
					tmp.parseHeadersOnly(headers);
					c.content_length = tmp.content_length;
					c.body_size = c.read_buffer.size() - (pos + 4);

					if (c.content_length <= 0)
					{
						tryParseRequest(c);
						return ;
					}
					if (c.content_length > c.max_body_size)
					{
						Server *server = _fd_to_Server[c.fd];
						c.write_buffer = server->buildErrorResponse(413);
						c.should_close = true;
						handleWrite(c);
						return;
					}
				}
			}
			if (c.headers_parsed)
			{
				size_t	pos = c.read_buffer.find("\r\n\r\n");
				c.body_size = c.read_buffer.size() - (pos + 4);
				if (c.body_size > c.max_body_size)
				{
					Server *server = _fd_to_Server[c.fd];
					c.write_buffer = server->buildErrorResponse(413);
					c.should_close = true;
					handleWrite(c);
					return;
				}
				if (c.content_length >= 0 && c.body_size >= c.content_length)
				{
					tryParseRequest(c);
					return;
				}
			}
		}
		else if (n == 0)
		{
			closeClient(c);
			return;
		}
		else
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;

			closeClient(c);
			return;
		}
	}
}

void ServerManager::enableWrite(int fd)
{
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.fd = fd;

	epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &ev);
}

void ServerManager::disableWrite(Client &c)
{
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = c.fd;

    epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, c.fd, &ev);
	c.body_size = 0;
	c.content_length = -1;
	c.headers_parsed = false;
}

void ServerManager::handleWrite(Client &c)
{
    if (c.write_buffer.empty())
    {
        disableWrite(c);
        return;
    }

    ssize_t n = send(c.fd, c.write_buffer.data(), c.write_buffer.size(), 0);

    if (n > 0)
    {
        c.write_buffer.erase(0, n);
    }
    else if (n == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return;
        }
        closeClient(c);
        return;
    }

    if (c.write_buffer.empty())
    {
        disableWrite(c);
		if (c.should_close)
			closeClient(c);
		else
		{
			c.state = Client::READING;
			c.read_buffer.clear();
			c.body_size = 0;
		}
    }
}


void ServerManager::closeClient(Client &c)
{
	if (_clients.find(c.fd) == _clients.end())
		return;
	LOG(
		Cyan("[") << "INFO" << Cyan("] ") <<
		Red << "Client (" << RESET
		<< c.fd <<
		Red << ") closed." << RESET
	);
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, c.fd, NULL);
	close(c.fd);
	_clients.erase(c.fd);
}


/* ************************************************************************** */
/*                                    Cgi                                     */
/* ************************************************************************** */

void ServerManager::handleCgiEvent(int fd)
{
	if (_cgi_fd_to_client.count(fd) == 0)
		return;

	int client_fd = _cgi_fd_to_client[fd];
	Client &c = _clients[client_fd];
	char buffer[4096];

	while (true)
	{
		ssize_t n = read(fd, buffer, sizeof(buffer));

		if (n > 0)
		{
			if (c.cgi.buffer.size() + (size_t)n > c.max_body_size)
			{
				kill(c.cgi.pid, SIGKILL);
				waitpid(c.cgi.pid, NULL, 0);
				epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, c.cgi.stdout_fd, NULL);
				close(c.cgi.stdout_fd);
				_cgi_fd_to_client.erase(c.cgi.stdout_fd);
				Server *server = _fd_to_Server[c.fd];
				c.write_buffer = server->buildErrorResponse(413);
				c.state = Client::WRITING;
				enableWrite(c.fd);
				return;
			}

			c.cgi.buffer.append(buffer, n);
		}
		else if (n == 0)
		{
			c.cgi.pipe_closed = true;
			break;
		}
		else
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;

			sendCgiError(c, 500);
			return;
		}
	}

	if (!c.cgi.process_done)
	{
		int status;
		pid_t ret = waitpid(c.cgi.pid, &status, WNOHANG);
		if (ret > 0)
			c.cgi.process_done = true;
	}

	if (c.cgi.pipe_closed && c.cgi.process_done)
	{
		finalizeCgi(c);
	}
}


static bool fileExists(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void ServerManager::launchCgi( const Request &req, Client &c,
		const std::string &path,
		const std::string &interpreter)
{
	if (!fileExists(path)) return sendCgiError(c, 404);

	int in_pipe[2];
	int out_pipe[2];

	if (pipe(in_pipe) < 0 || pipe(out_pipe) < 0)
	{
		closeClient(c);
		return;
	}

	pid_t pid = fork();
	if (pid < 0)
	{
		closeClient(c);
		return;
	}

	if (pid == 0)
	{
		dup2(in_pipe[0], STDIN_FILENO);
		dup2(out_pipe[1], STDOUT_FILENO);

		close(in_pipe[1]);
		close(out_pipe[0]);

		std::vector<std::string> env;
		env.push_back("REQUEST_METHOD=" + req.getMethod());
		env.push_back("SCRIPT_FILENAME=" + path);
		env.push_back("QUERY_STRING=" + req.getQuery());
		env.push_back("CONTENT_LENGTH=" + req.getHeader("Content-Length"));
		env.push_back("CONTENT_TYPE=" + req.getHeader("Content-Type"));

		std::vector<char*> envp;
		for (size_t i = 0; i < env.size(); i++)
			envp.push_back(const_cast<char*>(env[i].c_str()));
		envp.push_back(NULL);

		char *argv[3];
		argv[0] = const_cast<char*>(interpreter.c_str());
		argv[1] = const_cast<char*>(path.c_str());
		argv[2] = NULL;

		execve(interpreter.c_str(), argv, &envp[0]);
		perror("execve failed");
		exit(1);
	}

	close(in_pipe[0]);
	close(out_pipe[1]);

	fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);

	c.cgi.start_time = time(NULL);

	c.cgi.stdout_fd = out_pipe[0];
	c.cgi.stdin_fd = in_pipe[1];
	c.cgi.pid = pid;
	c.cgi.buffer.clear();

	c.cgi.pipe_closed = false;
	c.cgi.process_done = false;

	c.state = Client::CGI_RUNNING;

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = c.cgi.stdout_fd;

	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, c.cgi.stdout_fd, &ev);
	_cgi_fd_to_client[c.cgi.stdout_fd] = c.fd;

	if (req.getMethod() == "POST")
	{
		const std::string &body = req.getBody();
		if (!body.empty())
			write(c.cgi.stdin_fd, body.data(), body.size());
	}

	close(c.cgi.stdin_fd);
}

void ServerManager::finalizeCgi(Client &c)
{
	std::string &raw = c.cgi.buffer;

	size_t pos = raw.find("\r\n\r\n");
	if (pos == std::string::npos)
		pos = raw.find("\n\n");

	if (pos == std::string::npos)
	{
		sendCgiError(c, 500);
		cleanupCgi(c);
		return;
	}

	std::string headers = raw.substr(0, pos);
	std::string body = raw.substr(pos + (raw[pos + 1] == '\n' ? 2 : 4));

	Response res;
	res.setStatus(200);

	std::istringstream iss(headers);
	std::string line;

	while (std::getline(iss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		size_t sep = line.find(":");
		if (sep != std::string::npos)
		{
			std::string key = line.substr(0, sep);
			std::string value = line.substr(sep + 1);

			while (!value.empty() && value[0] == ' ')
				value.erase(0, 1);

			res.setHeader(key, value);
		}
	}

	res.setBody(body);

	c.write_buffer = res.build(true);
	enableWrite(c.fd);

	cleanupCgi(c);
}

void ServerManager::cleanupCgi(Client &c)
{
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, c.cgi.stdout_fd, NULL);
	close(c.cgi.stdout_fd);

	_cgi_fd_to_client.erase(c.cgi.stdout_fd);
}

void ServerManager::sendCgiError(Client &c, int errorCode)
{
	Server *server = _fd_to_Server[c.fd];
	c.write_buffer = server->buildErrorResponse(errorCode);
	c.state = Client::WRITING;
	enableWrite(c.fd);
}

#define CGI_TIMEOUT_SEC 1
void ServerManager::checkCgiTimeouts()
{
	time_t now = time(NULL);

	for (std::map<int, Client>::iterator it = _clients.begin();
			it != _clients.end(); ++it)
	{
		Client &c = it->second;

		if (c.state == Client::CGI_RUNNING)
		{
			if (now - c.cgi.start_time > CGI_TIMEOUT_SEC)
			{
				kill(c.cgi.pid, SIGKILL);
				waitpid(c.cgi.pid, NULL, 0);

				epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, c.cgi.stdout_fd, NULL);
				close(c.cgi.stdout_fd);
				_cgi_fd_to_client.erase(c.cgi.stdout_fd);

				Server *server = _fd_to_Server[c.fd];
				c.write_buffer = server->buildErrorResponse(504);
				c.state = Client::WRITING;
				enableWrite(c.fd);
			}
		}
	}
}
