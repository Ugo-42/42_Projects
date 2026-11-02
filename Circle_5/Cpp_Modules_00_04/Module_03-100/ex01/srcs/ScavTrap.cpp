/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:51:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/06 10:24:34 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


ScavTrap::ScavTrap() : ClapTrap("ScavTrap")
{
	_hp = 100;
	_mana = 50;
	_dmg = 20;
	LOG(hex(0x6ca642) + "ScavTrap Default constructor called" + RESET);
}

ScavTrap::ScavTrap(const t_string& name) : ClapTrap(name)
{
	_hp = 100;
	_mana = 50;
	_dmg = 20;
	LOG(hex(0x6ca642) + "ScavTrap Name constructor called" + RESET);
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	LOG(hex(0x6ca642) + "ScavTrap Copy constructor called" + RESET);
}


ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	if (this != &other)
	{
		ClapTrap::operator=(other);
	}
	LOG(hex(0x6ca642) + "ScavTrap Copy assignment operator called" + RESET);
	return *this;
}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


ScavTrap::~ScavTrap()
{
	LOG(hex(0xc23030) + "ScavTrap Destructor called" + RESET);
}


/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */


void ScavTrap::attack(const t_string& target)
{
	const t_string stats = "[💖" + to_string(_hp)
		+ "|🔋" + to_string(_mana)
		+ "|⚔️ " + to_string(_dmg) + "]";

	PRINT("ScavTrap " << _name << " " << stats);
	if (!_mana || !_hp)
	{
		ECHO(" is unable to attack!");
		return ;
	}
	ECHO(rgb(255,110,210) << " attacks " << RESET << target
		<< ", causing "	<< _dmg << " points of damage!");
	_mana--;
}

void ScavTrap::guardGate()
{
	ECHO("ScavTrap " << _name << " is now in Gate keeper mode");
}

