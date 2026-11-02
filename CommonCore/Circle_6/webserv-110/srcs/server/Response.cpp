/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:14:32 by vvalenti          #+#    #+#             */
/*   Updated: 2026/03/30 11:23:16 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() : _status_code(200), _status_msg("OK") {
	_status_map[100] = "Continue";
    _status_map[101] = "Switching Protocols";

    _status_map[200] = "OK";
    _status_map[201] = "Created";
    _status_map[202] = "Accepted";
    _status_map[203] = "Non-Authoritative Information";
    _status_map[204] = "No Content";
    _status_map[205] = "Reset Content";
    _status_map[206] = "Partial Content";

    _status_map[300] = "Multiple Choices";
    _status_map[301] = "Moved Permanently";
    _status_map[302] = "Found";
    _status_map[303] = "See Other";
    _status_map[304] = "Not Modified";
    _status_map[305] = "Use Proxy";
    _status_map[307] = "Temporary Redirect";

    _status_map[400] = "Bad Request";
    _status_map[401] = "Unauthorized";
    _status_map[402] = "Payment Required";
    _status_map[403] = "Forbidden";
    _status_map[404] = "Not Found";
    _status_map[405] = "Method Not Allowed";
    _status_map[406] = "Not Acceptable";
    _status_map[407] = "Proxy Authentication Required";
    _status_map[408] = "Request Timeout";
    _status_map[409] = "Conflict";
    _status_map[410] = "Gone";
    _status_map[411] = "Length Required";
    _status_map[412] = "Precondition Failed";
    _status_map[413] = "Payload Too Large";
    _status_map[414] = "URI Too Long";
    _status_map[415] = "Unsupported Media Type";
    _status_map[416] = "Range Not Satisfiable";
    _status_map[417] = "Expectation Failed";
    _status_map[418] = "I'm a Teapot";
    _status_map[426] = "Upgrade Required";

    _status_map[500] = "Internal Server Error";
    _status_map[501] = "Not Implemented";
    _status_map[502] = "Bad Gateway";
    _status_map[503] = "Service Unavailable";
    _status_map[504] = "Gateway Timeout";
    _status_map[505] = "HTTP Version Not Supported";
}

Response::~Response(){}


void	Response::setStatus(int code)
{
	_status_code = code;

	std::map<int, std::string>::const_iterator it = _status_map.find(code);
	if (it != _status_map.end())
		_status_msg = it->second;
	else
		_status_msg = "Unknow Status";

	if (_status_code == 204)
	{
		_headers["Content-Length"] = "0";
	}
}


void	Response::setBody(std::string const &body)
{
	_body = body;

	std::stringstream ss;
	ss << body.length();

	_headers["Content-Length"] = ss.str();
}


void	Response::setHeader(std::string const &key, std::string const &value)
{
	_headers[key] = value;
}


std::string	Response::build(bool includeBody)
{
	std::stringstream	response;

	response << "HTTP/1.1 "
			 << _status_code
			 << " "
			 << _status_msg
			 << "\r\n";
	
	if (!_body.empty())
	{	
		_headers["Content-Length"] = to_string(_body.size());
	}
	else
		_headers["Content-Length"] = "0";
	
	std::map<std::string, std::string>::const_iterator it;
	for (it = _headers.begin(); it != _headers.end(); ++it)
		response << it->first << ": " << it->second << "\r\n";

	response << "\r\n";

	if (includeBody)
		response << _body;
	
	return response.str();
}

std::string	Response::getStatusMsg()
{
	return _status_msg;
}