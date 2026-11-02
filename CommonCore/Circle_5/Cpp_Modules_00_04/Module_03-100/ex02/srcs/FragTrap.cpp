/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:51:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/07 14:42:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


FragTrap::FragTrap() : ClapTrap("FragTrap")
{
	_hp = 100;
	_mana = 100;
	_dmg = 30;
	LOG(hex(0x6ca642) + "Default FragTrap constructor called" + RESET);
}

FragTrap::FragTrap(const t_string& name) : ClapTrap(name)
{
	_hp = 100;
	_mana = 100;
	_dmg = 30;
	LOG(hex(0x6ca642) + "FragTrap Name constructor called" + RESET);
}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


FragTrap::~FragTrap()
{
	LOG(hex(0xc23030) + "FragTrap Destructor called" + RESET);
}


/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */


void FragTrap::attack(const t_string& target)
{
	const t_string stats = "[💖" + to_string(_hp)
		+ "|🔋" + to_string(_mana)
		+ "|⚔️ " + to_string(_dmg) + "]";

	PRINT("FragTrap " << _name << " " << stats);
	if (!_mana || !_hp)
	{
		ECHO(" is unable to attack!");
		return ;
	}
	ECHO(rgb(255,155,55) << " attacks " << RESET << target
		<< ", causing "	<< _dmg << " points of damage!");
	_mana--;
}

void FragTrap::highFivesGuys()
{
	ECHO("FragTrap " << _name << ": " << ITALIC << "High-Fives Guys!" << RESET);
}
