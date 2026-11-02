/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 09:19:01 by vvalenti          #+#    #+#             */
/*   Updated: 2026/04/07 13:19:02 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"




Request::Request() {content_length = 0;}

Request::~Request() {}

const std::string	&Request::getBody() const {
	return _body;
}

const std::string	&Request::getMethod() const {
	return _method;
}

const std::string	&Request::getPath() const {
	return _path;
}

const std::string	&Request::getQuery() const {
	return _query;
}

const std::string	&Request::getVersion() const {
	return _version;
}

static std::string toLower(const std::string &s)
{
    std::string res = s;
    for (size_t i = 0; i < res.size(); i++)
    {
        if (res[i] >= 'A' && res[i] <= 'Z')
            res[i] += 32;
    }
    return res;
}

const std::string& Request::getHeader(const std::string &key) const
{
	static const std::string empty = "";

	std::string lower = toLower(key);

	std::map<std::string, std::string>::const_iterator it = _headers.find(lower);
	if (it != _headers.end())
		return it->second;
	return empty;
}

const std::map<std::string, std::string>	&Request::getHeaders() const {
	return _headers;
}



bool Request::parseHeadersOnly(const std::string &raw)
{
	size_t pos = raw.find("\r\n\r\n");
	if (pos == std::string::npos)
		return false;

	std::istringstream stream(raw.substr(0, pos + 2));
	std::string line;

	if (!getline(stream, line))
		return false;
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1);

	std::istringstream requestLine(line);
	std::string fullPath;

	requestLine >> _method >> fullPath >> _version;
	if (_method.empty() || fullPath.empty() || _version.empty())
		return false;

	size_t qpos = fullPath.find('?');
	if (qpos != std::string::npos)
	{
		_path = fullPath.substr(0, qpos);
		_query = fullPath.substr(qpos + 1);
	}
	else
	{
		_path = fullPath;
		_query = "";
	}

	while (getline(stream, line))
	{
		if (line == "\r" || line == "")
			break;

		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		size_t colon = line.find(':');
		if (colon == std::string::npos)
			continue;

		std::string key = toLower(line.substr(0, colon));
		std::string value = line.substr(colon + 1);

		if (!value.empty() && value[0] == ' ')
			value.erase(0, 1);

		_headers[key] = value;
	}

	content_length = 0;
	if (_headers.find("content-length") != _headers.end())
		content_length = std::atoi(_headers["content-length"].c_str());

	return true;
}


bool Request::parse(const std::string &raw)
{
	size_t pos = raw.find("\r\n\r\n");
	if (pos == std::string::npos)
		return false;
		
	if (!parseHeadersOnly(raw))
		return false;

	size_t body_start = pos + 4;

	if (raw.size() < body_start)
		return false;

	_body = raw.substr(body_start);

	if (_body.size() < content_length)
		return false;

	return true;
}
