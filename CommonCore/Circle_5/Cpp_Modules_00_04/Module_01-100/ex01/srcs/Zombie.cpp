/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:12:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/06 11:08:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <unistd.h>

Zombie::Zombie()
{
	std::cout
		<< rgb(255, 179, 0)
		<< "A Zombie has risen from the dead!"
		<< RESET
		<< std::endl;
}

Zombie::~Zombie()
{
	std::cout
		<< rgb(255, 0, 0)
		<< _name
		<< " has been destroyed."
		<< RESET
		<< std::endl;
}

void Zombie::announce( void )
{
	std::cout
		<< rgb(25, 155, 0)
		<< _name
		<< ": BraiiiiiiinnnzzzZ..."
		<< RESET
		<< std::endl;
}

void Zombie::setName( t_string name )
{
	_name = name;
}
