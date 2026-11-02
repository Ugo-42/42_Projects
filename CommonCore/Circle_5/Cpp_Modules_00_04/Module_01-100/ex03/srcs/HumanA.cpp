/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:24:37 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/13 14:30:41 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

HumanA::HumanA(const t_string& name, Weapon& weapon)
	: _name(name), _weapon(weapon) {}

void HumanA::attack() const
{
	ECHO(_name << str_hex(" attacks", 0xC40000) << " with "
			<< ITALIC << str_hex(_weapon.getType(), 0x448800) << RESET);
}

HumanA::~HumanA() {}
