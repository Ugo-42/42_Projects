/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:36:13 by vvalenti          #+#    #+#             */
/*   Updated: 2026/03/11 18:04:00 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Router.hpp"

Router::Router() {}

Router::~Router() {}


void Router::addLocation(const Location &loc)
{
	_locations.push_back(loc);
}

const Location* Router::match(const std::string &path) const
{
	const Location* best = NULL;
	size_t best_len = 0;

	for (size_t i = 0; i < _locations.size(); i++)
	{
		const std::string &locPath = _locations[i].getPath();

		if (path.find(locPath) == 0)
		{
			if (locPath.length() > best_len)
			{
				best = &_locations[i];
				best_len = locPath.length();
			}
		}
	}

	return best;
}
