/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:34:12 by vvalenti          #+#    #+#             */
/*   Updated: 2026/03/11 18:04:55 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class Location
{
	private:

		bool _autoIndexOn;
		bool _uploadEnable;
		std::string _path;
		std::string _root;
		std::string _index;
		std::vector<std::string> _methods;
		std::pair<int, std::string> _redirect;
		std::map<std::string, std::string> _cgiMap;

	public:

		Location();
		~Location();

		void	setAutoIndex(bool autoIndex);
		void	setUploadEnable(bool Upload);
		void	setPath(const std::string &path);
		void	setCgiMap(const std::map<std::string, std::string> &path);
		void	setRoot(const std::string &root);
		void	setIndex(const std::string &index);
		void	setRedirect(const std::pair<int, std::string> &redirect);
		void	addMethod(std::vector<std::string> &method);

		bool	isCgi(const std::string &path) const;
		bool	isAutoIndexOn() const;
		bool	isUploadEnable() const;
		bool	isMethodAllowed(const std::string &method) const;

		std::string	getCgiInterpreter(const std::string &path) const;

		const std::map<std::string, std::string>	&getCgiMap() const;
		const std::pair<int, std::string>			&getRedirect() const;
		const std::string							&getIndex() const;
		const std::string							&getPath() const;
		const std::string							&getRoot() const;
		const std::vector<std::string>				&getMethods() const;
};

