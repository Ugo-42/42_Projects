/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:35:04 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/06 10:15:46 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#pragma once

class ClapTrap
{
	protected:
		const t_string  _name;
		unsigned int    _hp;
		unsigned int    _mana;
		unsigned int    _dmg;

	public:
		ClapTrap();
		ClapTrap(const t_string& name);
		ClapTrap(const ClapTrap& other);
		ClapTrap& operator=(const ClapTrap& other);
		~ClapTrap();

		virtual void attack(const t_string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};
