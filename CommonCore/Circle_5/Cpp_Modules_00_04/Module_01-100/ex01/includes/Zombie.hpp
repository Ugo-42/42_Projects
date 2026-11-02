/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:59:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/06 10:37:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "config.hpp"

class Zombie
{
	private:
		t_string _name;

	public:
		Zombie();
		~Zombie();

		void announce( void );
		void setName( t_string name );
};

#endif
