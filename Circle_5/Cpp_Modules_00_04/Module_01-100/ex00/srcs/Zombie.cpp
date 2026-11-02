/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:12:05 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/12 09:13:31 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <unistd.h>

Zombie::Zombie(t_string name) : _name(name)
{
	std::cout
		<< rgb(255, 179, 0)
		<< name
		<< " has joined the game!"
		<< RESET
		<< std::endl;
}

Zombie::~Zombie()
{
	std::cout
		<< rgb(255, 0, 0)
		<< _name
		<< " fell out of the world."
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
