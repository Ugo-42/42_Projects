/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:35:04 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/06 10:23:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
	private:
		t_string _name;

	public:
		DiamondTrap();
		DiamondTrap(const t_string& name);
		~DiamondTrap();

		void attack(const t_string& target);
		void whoAmI();
};
