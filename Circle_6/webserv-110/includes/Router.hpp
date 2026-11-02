/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:33:06 by vvalenti          #+#    #+#             */
/*   Updated: 2026/03/26 04:34:42 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include "header.hpp"
#include "Location.hpp"


class Location;


class Router
{
	private :
	
		std::vector<Location> _locations;
	
	public :
	
		Router();
		~Router();

		void addLocation(const Location &loc);
		const Location* match(const std::string &path) const;

};

