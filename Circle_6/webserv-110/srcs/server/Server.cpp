/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:02:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/04/07 12:22:12 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "client.hpp"
#include "ServerManager.hpp"

Server::Server(t_server serv)
	: _serverName(serv.server_name)
	, _ip(serv.ip)
	, _port(serv.port)
	, _max_body_size(serv.client_max_body_size)
	, _root(serv.root)
	, _error_pages(serv.error_pages)
{
	for (size_t i = 0; i < serv.locations.size(); i++)
	{
		Location	loc;

		loc.setAutoIndex(serv.locations[i].autoindex);
		loc.setUploadEnable(serv.locations[i].upload_enable);
		loc.setPath(serv.locations[i].path);
		loc.setCgiMap(serv.locations[i].cgi);
		loc.setRoot(serv.locations[i].root);
		loc.setIndex(serv.locations[i].index);
		loc.setRedirect(serv.locations[i].redirect);
		loc.addMethod(serv.locations[i].methods);
		_router.addLocation(loc);
	}
	setupSocket();
}

Server::~Server(){}


/* ************************************************************************** */
/*                                Helpers                                     */
/* ************************************************************************** */


static bool isDirectory(const std::string &path)
{
	struct stat path_stat;
	if (stat(path.c_str(), &path_stat) != 0)
		return false;
	return S_ISDIR(path_stat.st_mode);
}


static bool isRegularFile(const std::string &path)
{
	struct stat path_stat;
	if (stat(path.c_str(), &path_stat) != 0)
		return false;
	return S_ISREG(path_stat.st_mode);
}


#include "autoIndexTemplate.hpp"
static std::string generateAutoindex(const std::string &dir_path, const std::string &url_path)
{
	std::stringstream files;

	DIR *dir = opendir(dir_path.c_str());
	if (dir)
	{
		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL)
		{
			std::string name = entry->d_name;
			if (name == ".")
				continue;

			std::string full = dir_path + "/" + name;
			bool is_dir = isDirectory(full);

			if (is_dir)
				name += "/";

			files << "<li><a class=\""
				  << (is_dir ? "dir" : "file")
				  << "\" href=\"" << name << "\">"
				  << (is_dir ? "📁 " : "📄 ")
				  << name
				  << "</a></li>\n";
		}
		closedir(dir);
	}

	std::string html = AUTOINDEX_TEMPLATE;

	size_t pos;
	while ((pos = html.find("{{FILES}}")) != std::string::npos)
		html.replace(pos, 9, files.str());

	while ((pos = html.find("{{PATH}}")) != std::string::npos)
		html.replace(pos, 8, url_path);

	return html;
}


/* ************************************************************************** */
/*                               Exectution                                   */
/* ************************************************************************** */


std::string	Server::handleRequest(const Request &req, Client &c, ServerManager &mgr)
{
	int status = validateRequest(req);
	if (status != 1)
		return buildErrorResponse(status);

	return executeRequest(req, c, mgr);
}


std::string Server::executeRequest(const Request &req, Client &c, ServerManager &mgr)
{
	bool forbidden = false;

	std::string clean_path = decodeURL(req.getPath());
	clean_path = normalizePath(clean_path, forbidden);
	if (clean_path != "/" && clean_path[0] != '/')
	clean_path = "/" + clean_path;

	if (forbidden)
		return buildErrorResponse(403);


	/* -------------- ROUTER --------------- */

	const Location *loc = _router.match(clean_path);
	if (!loc)
		return buildErrorResponse(404);

	if (!loc->isMethodAllowed(req.getMethod()))
		return buildErrorResponse(405);

	/* -------------- PATH BUILD --------------- */

	// Trim virtual root
	std::string remainder = clean_path;
	std::string loc_path = loc->getPath();
	if (loc_path != "/" && remainder.find(loc_path) == 0)
		remainder = remainder.substr(loc_path.length());
	if (!remainder.empty() && remainder[0] == '/')
		remainder = remainder.substr(1);

	// Append filesystem root
	std::string file_path = FS_SRV_ROOT;
	std::string loc_root = loc->getRoot();
	if (!loc_root.empty() && loc_root[0] != '/')
		file_path += "/";
	file_path += loc_root;
	if (!remainder.empty())
		file_path += "/" + remainder;

	/* ------------- HANDLE CGI -------------- */

	if (loc->isCgi(file_path))
	{
		std::string interpreter = loc->getCgiInterpreter(file_path);
		//TODO: Check if valid executable else return Error

		mgr.launchCgi(req, c, file_path, interpreter);
		return "";
	}

	/* -------------- REDIRECT --------------- */

	const std::pair<int, std::string> &redirect = loc->getRedirect();
	if (redirect.first != 0)
	{
		Response res;
		res.setStatus(redirect.first);
		res.setHeader("Location", redirect.second);
		return res.build(req.getMethod() != "HEAD");
	}

	/* -------------- DIRECTORY / AUTOINDEX --------------- */

	std::string body;

	if (isDirectory(file_path))
	{
		if (req.getPath()[req.getPath().length() - 1] != '/')
		{
			Response res;
			res.setStatus(301);
			res.setHeader("Location", req.getPath() + "/");
			return res.build(req.getMethod() != "HEAD");
		}

		std::string indexPath = file_path + "/" + loc->getIndex();
		if (isRegularFile(indexPath))
		{
			readFile(indexPath, body);
			Response res;
			res.setHeader("Content-Type", getContentType(indexPath));
			res.setBody(body);
			return res.build(req.getMethod() != "HEAD");
		}

		if (loc->isAutoIndexOn())
		{
			std::string listing = generateAutoindex(file_path, clean_path);
			Response res;
			res.setHeader("Content-Type", "text/html");
			res.setBody(listing);
			return res.build(req.getMethod() != "HEAD");
		}

		return buildErrorResponse(403);
	}

	/* -------------- Handle Method ---------------- */

	if (req.getMethod() == "GET")
		return handleGET(loc, file_path, false);
	else if (req.getMethod() == "HEAD")
		return handleGET(loc, file_path, true);
	else if (req.getMethod() == "DELETE")
		return handleDELETE(file_path);
	else if (req.getMethod() == "POST")
	{
		if (!loc->isUploadEnable())
			return buildErrorResponse(403);
		return handlePOST(req, file_path);
	}

	return buildErrorResponse(405);
}


/* ************************************************************************** */
/*                               Handle Method                                */
/* ************************************************************************** */


std::string Server::handleGET(const Location *loc, std::string file_path, bool head)
{
	std::string body;

	int status = checkPathNoSend(file_path, loc);
	if (status != 1)
		return buildErrorResponse(status);

	if (!readFile(file_path, body))
		return buildErrorResponse(404);

	Response res;
	res.setHeader("Content-Type", getContentType(file_path));
	res.setBody(body);

	return res.build(!head);
}

std::string Server::handlePOST(const Request &req, std::string file_path)
{
    std::string body = req.getBody();

    if (body.empty())
        return buildErrorResponse(400);

    std::ofstream out(file_path.c_str(), std::ios::binary);
    if (!out.is_open())
        return buildErrorResponse(500);

    out << body;
    out.close();

    Response res;
    res.setStatus(201);
    res.setHeader("Content-Type", "text/html");
    res.setBody("<h1>201 Created</h1>");

    return res.build(true);
}

std::string Server::handleDELETE(std::string file_path)
{
    struct stat path_stat;

    if (stat(file_path.c_str(), &path_stat) != 0)
        return buildErrorResponse(404);

    if (S_ISDIR(path_stat.st_mode))
        return buildErrorResponse(403);

    if (remove(file_path.c_str()) != 0)
        return buildErrorResponse(500);

    Response res;
    res.setStatus(204);

    return res.build(true);
}


/* ************************************************************************** */
/*                                  Utils                                     */
/* ************************************************************************** */


int		Server::getFd() const       { return _server_fd; }
size_t	Server::getMaxBodySize() const { return _max_body_size; }


void	Server::setupSocket()
{

	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd < 0)
		throw std::runtime_error(rgb(255,0,0)("Socket failed"));

	fcntl(_server_fd, F_SETFL, O_NONBLOCK);

	int	opt = 1;
	setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	_address.sin_family = AF_INET;
	_address.sin_port = htons(_port);
	if (_ip == "localhost")
		_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	else
		_address.sin_addr.s_addr = inet_addr(_ip.c_str());

	if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
		throw std::runtime_error(rgb(255,0,0)("Bind failed"));
	if (listen(_server_fd, 10) < 0)
		throw std::runtime_error(rgb(255,0,0)("listen failed"));
	ECHO("Server listening on port " << _port);
}


bool	Server::readFile(std::string const &filename, std::string &content)
{
    std::ifstream file(filename.c_str(), std::ios::binary);
	if (!file.is_open())
		return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
	content = buffer.str();
	return true;
}


int Server::checkPathNoSend(std::string &filename, const Location *loc)
{
	struct stat path_stat;

	if (filename.empty())
		return 400;

	if (stat(filename.c_str(), &path_stat) != 0)
		return 404;

	if (S_ISDIR(path_stat.st_mode))
	{
		std::string index = loc->getIndex();
		if (index.empty())
			index = "index.html";

		if (filename[filename.length() - 1] != '/')
			filename += "/";

		std::string try_path = filename + index;
		if (stat(try_path.c_str(), &path_stat) == 0)
			filename = try_path;
		else
			return 403;
	}
	return 1;
}


int Server::validateRequest(const Request &req)
{
	if (req.getMethod() != "GET" &&
		req.getMethod() != "POST" &&
		req.getMethod() != "HEAD" &&
		req.getMethod() != "DELETE")
	{
		return 405;
	}
	if (req.getVersion() != "HTTP/1.1")
	{
		return 505;
	}
	return 1;
}


std::string Server::decodeURL(const std::string &path)
{
	std::string result;

	for (size_t i = 0; i < path.length(); i++)
	{
		if (path[i] == '%' && i + 2 < path.length())
		{
			std::string hex = path.substr(i + 1, 2);
			char c = static_cast<char>(strtol(hex.c_str(), NULL, 16));
			result += c;
			i += 2;
		}
		else
			result += path[i];
	}
	return result;
}


std::string	Server::normalizePath(std::string const &path, bool &forbidden)
{
    std::vector<std::string>	stack;
    std::stringstream			ss(path);
    std::string					segment;

	while (getline(ss, segment, '/'))
	{
		if (segment.empty() || segment == ".")
			continue;
		if (segment == "..")
		{
			if (stack.empty())
			{
				forbidden = true;
				return "";
			}
			stack.pop_back();
		}
		else
			stack.push_back(segment);
	}
	std::string clean_path;
	for (size_t i = 0; i < stack.size(); ++i)
	{
		clean_path += stack[i];
		if (i != stack.size() - 1)
			clean_path += "/";
	}

	return clean_path;
}


std::string Server::buildErrorResponse(int code)
{
	Response res;

	res.setStatus(code);
	res.setHeader("Content-Type", "text/html");

	std::string body;

	if (!_error_pages[code].empty() && readFile(_error_pages[code], body))
		res.setBody(body);
	else
	{
		std::stringstream ss;
		ss << "<h1>" << code << " " << res.getStatusMsg() << "</h1>\n";
		res.setBody(ss.str());
	}

	return res.build(true);
}


std::string Server::getContentType(const std::string &path)
{
	size_t dot = path.find_last_of('.');

	if (dot == std::string::npos)
		return "text/plain";

	std::string ext = path.substr(dot);

	if (ext == ".html")
		return "text/html";
	if (ext == ".css")
		return "text/css";
	if (ext == ".js")
		return "application/javascript";
	if (ext == ".png")
		return "image/png";
	if (ext == ".jpg" || ext == ".jpeg")
		return "image/jpeg";
	if (ext == ".gif")
		return "image/gif";
	if (ext == ".ico")
		return "image/x-icon";

	return "text/plain";
}
