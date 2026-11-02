/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:02 by vvalenti          #+#    #+#             */
/*   Updated: 2026/04/07 12:27:29 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"
#include "Server.hpp"
#include "client.hpp"

class Server;

class ServerManager
{
	private:

		t_config					_config;
		std::vector<Server>			_servers;
		std::map<int, Server*>		_fd_to_Server;
		std::map<int, std::string>	_client_Buffers;
		std::set<int>				_serverFds;
		std::set<int>				_clientFds;
		std::map<int, Client>		_clients;
		std::map<int, int>			_cgi_fd_to_client;

		int		_epoll_fd;

		void	handleClient(int client_fd);
		void	handleNewConnection(int server_fd);
		void	handleClientEvent(int fd, uint32_t events);
		void	handleRead(Client &c);
		void	handleWrite(Client &c);
		void	closeClient(Client &c);
		void	tryParseRequest(Client &c);
		void	enableWrite(int fd);
		void	disableWrite(Client &c);

		void	checkCgiTimeouts();
		void	cleanupCgi(Client &c);
		void	finalizeCgi(Client &c);
		void	handleCgiEvent(int fd);
		void	sendCgiError(Client &c, int errorCode);

	public:

		ServerManager(t_config config);
		~ServerManager();

		void	run();
		void	launchCgi(const Request &req, Client &c, const std::string &path, const std::string &interpreter);

};

