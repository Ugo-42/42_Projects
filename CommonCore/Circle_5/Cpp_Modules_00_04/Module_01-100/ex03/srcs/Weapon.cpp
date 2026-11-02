/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:24:47 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/13 11:56:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

Weapon::Weapon(const t_string& type) : _type(type) {}

const t_string& Weapon::getType() const {
	return _type;
}

void Weapon::setType(const t_string& type) {
	_type = type;
}

Weapon::~Weapon() {}
