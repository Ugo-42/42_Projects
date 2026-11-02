/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:47:59 by vvalenti          #+#    #+#             */
/*   Updated: 2026/03/30 11:23:13 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class Response
{
	private :
	
		int									_status_code;
		std::string							_status_msg;
		std::string							_body;
		std::map<std::string, std::string>	_headers;
		std::map<int, std::string>			_status_map;

	public :

		Response();
		~Response();

		void	setStatus(int code);
		void	setBody(std::string const &body);
		void	setHeader(std::string const &key, std::string const &value);

		std::string	getStatusMsg();

		std::string	build(bool includeBody);

};
