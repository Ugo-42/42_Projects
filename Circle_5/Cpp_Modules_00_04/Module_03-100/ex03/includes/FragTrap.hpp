/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:35:04 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/07 14:42:50 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#pragma once

class FragTrap : virtual public ClapTrap
{
	public:
		FragTrap();
		FragTrap(const t_string& name);
		~FragTrap();

		void attack(const t_string& target);
		void highFivesGuys();
};
