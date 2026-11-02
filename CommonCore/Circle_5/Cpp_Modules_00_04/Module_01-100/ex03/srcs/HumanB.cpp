/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:24:37 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/13 14:30:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

HumanB::HumanB(const t_string& name) : _name(name), _weapon(NULL) {}

void HumanB::attack() const {
	if (_weapon)
	{
		ECHO(_name << str_hex(" attacks", 0xC40000) << " with "
				<< ITALIC << str_hex(_weapon->getType(), 0x448800) << RESET);
	}
	else
		ECHO(_name << " has no weapon!");
}

void HumanB::setWeapon(Weapon& weapon) {
	_weapon = &weapon;
}

HumanB::~HumanB() {}
