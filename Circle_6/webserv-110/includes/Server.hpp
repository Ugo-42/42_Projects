/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 11:04:18 by vvalenti          #+#    #+#             */
/*   Updated: 2026/03/27 16:40:57 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Location.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Router.hpp"
#include "header.hpp"

class Request;

class Router;

struct t_config;
struct Client;

class ServerManager;

class Server
{
	private:

		const std::string			_serverName;
		const std::string			_ip;
		const int					_port;

		size_t						_max_body_size;

		int							_server_fd;
		struct sockaddr_in			_address;
		std::string					_root;
		std::map<int, std::string>	_error_pages;
		Router						_router;

		void		setupSocket();
		int			validateRequest(const Request &req);

		std::string	executeRequest(const Request &req, Client &c, ServerManager &mgr);

		bool	readFile(std::string const &filename, std::string &content);

		std::string normalizePath(std::string const &path, bool &forbidden);
		std::string decodeURL(const std::string &path);
		std::string getContentType(const std::string &path);


		std::string handleGET(const Location *loc, std::string file_path, bool head);
		std::string handlePOST(const Request &req, std::string file_path);
		std::string handleDELETE(std::string file_path);

		int checkPathNoSend(std::string &filename, const Location *loc);

	public:
		std::string	buildErrorResponse(int code);
		void		sendError(int code, int client_fd);

		Server(t_server server);
		~Server();

		int		getFd() const;
		size_t	getMaxBodySize() const;
		std::string	handleRequest(const Request &req, Client &c, ServerManager &mgr);

};
