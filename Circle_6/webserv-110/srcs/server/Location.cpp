/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:36:05 by vvalenti          #+#    #+#             */
/*   Updated: 2026/04/07 14:25:56 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"


Location::Location() {}
Location::~Location() {}

/* ************************************************************************** */

void Location::addMethod(std::vector<std::string> &method) {
	_methods.insert(_methods.end(), method.begin(), method.end());
}

void Location::setAutoIndex(bool autoIndex)       { _autoIndexOn = autoIndex; }
void Location::setUploadEnable(bool upload)       { _uploadEnable = upload; }
void Location::setIndex(const std::string &index) { _index = index; }
void Location::setPath(const std::string &path)   { _path = path; }
void Location::setRoot(const std::string &root)   { _root = root; }

void Location::setCgiMap(const std::map<std::string, std::string> &cgiMap) {
	_cgiMap = cgiMap;
}
void Location::setRedirect(const std::pair<int, std::string> &redirect) {
	_redirect = redirect;
}

/* ************************************************************************** */

bool Location::isAutoIndexOn() const  { return _autoIndexOn; }
bool Location::isUploadEnable() const { return _uploadEnable; }

const std::string &Location::getIndex() const { return _index; }
const std::string &Location::getPath() const  { return _path; }
const std::string &Location::getRoot() const  { return _root; }

const std::map<std::string, std::string> &Location::getCgiMap() const {
	return _cgiMap;
}
const std::pair<int, std::string> &Location::getRedirect() const {
	return _redirect;
}
const std::vector<std::string> &Location::getMethods() const {
	return _methods;
}

bool Location::isMethodAllowed(const std::string &method) const
{
	for (size_t i = 0; i < _methods.size(); i++)
	{
		if (_methods[i] == method)
			return true;
	}
	return false;
}


static bool endsWith(const std::string &str, const std::string &suffix) {
	if (str.length() < suffix.length())
		return false;
	return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool Location::isCgi(const std::string &path) const
{
	for (std::map<std::string, std::string>::const_iterator it = _cgiMap.begin();
			it != _cgiMap.end(); ++it)
	{
		if (endsWith(path, it->first))
			return true;
	}
	return false;
}

std::string Location::getCgiInterpreter(const std::string &path) const
{
    for (std::map<std::string, std::string>::const_iterator it = _cgiMap.begin();
         it != _cgiMap.end(); ++it)
    {
        if (endsWith(path, it->first))
            return it->second;
    }
    return "";
}

