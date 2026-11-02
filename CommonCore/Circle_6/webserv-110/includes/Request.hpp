/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 09:17:49 by vvalenti          #+#    #+#             */
/*   Updated: 2026/04/07 13:15:49 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class Request
{
	private :

		std::string _method;
		std::string _path;
		std::string _query;
		std::string _version;
		std::map<std::string, std::string> _headers;
		std::string _body;

	public :

		Request();
		~Request();

		bool parse(const std::string &rawRequest);
		bool parseHeadersOnly(const std::string &raw);

		const std::string							&getMethod() const;
		const std::string							&getPath() const;
		const std::string							&getQuery() const;
		const std::string							&getVersion() const;
		const std::string							&getBody() const;
		const std::string							&getHeader(const std::string &key) const;
		const std::map<std::string, std::string>	&getHeaders() const;
		
		size_t		content_length;
};
