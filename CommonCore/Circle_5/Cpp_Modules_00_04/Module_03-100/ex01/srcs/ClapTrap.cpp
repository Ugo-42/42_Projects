/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:51:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/04 12:12:46 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


ClapTrap::ClapTrap() : _name("ClapTrap"), _hp(10), _mana(10), _dmg(0)
{
	LOG(hex(0x6ca642) + "ClapTrap Default constructor called" + RESET);
}

ClapTrap::ClapTrap(const t_string& name) : _name(name), _hp(10), _mana(10), _dmg(0)
{
	LOG(hex(0x6ca642) + "ClapTrap Name constructor called" + RESET);
}

ClapTrap::ClapTrap(const ClapTrap& other)
	: _name(other._name), _hp(other._hp), _mana(other._mana), _dmg(other._dmg)
{
	LOG(hex(0x6ca642) + "ClapTrap Copy constructor called" + RESET);
}


ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	if (this != &other)
	{
		_hp = other._hp;
		_mana = other._mana;
		_dmg = other._dmg;
	}
	LOG(hex(0x6ca642) + "ClapTrap Copy assignment operator called" + RESET);
	return *this;
}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


ClapTrap::~ClapTrap()
{
	LOG(hex(0xc23030) + "ClapTrap Destructor called" + RESET);
}


/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */


void ClapTrap::attack(const t_string& target)
{
	const t_string stats = "[💖" + to_string(_hp)
		+ "|🔋" + to_string(_mana)
		+ "|⚔️ " + to_string(_dmg) + "]";

	PRINT("ClapTrap " << _name << " " << stats);
	if (!_mana || !_hp)
	{
		ECHO(" is unable to attack!");
		return ;
	}
	ECHO(rgb(110,210,255) << " attacks " << RESET << target
		<< ", causing "	<< _dmg << " points of damage!");
	_mana--;
}

void ClapTrap::takeDamage(unsigned int amount)
{

	const t_string stats = "[💖" + to_string(_hp)
		+ "|🔋" + to_string(_mana)
		+ "|⚔️ " + to_string(_dmg) + "]";

	ECHO("ClapTrap " << _name << " " << stats << " lost " << amount << " health points!");
	if (amount > _hp)
		_hp = 0;
	else
		_hp -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	const t_string stats = "[💖" + to_string(_hp)
		+ "|🔋" + to_string(_mana)
		+ "|⚔️ " + to_string(_dmg) + "]";

	PRINT("ClapTrap " << _name << " " << stats);
	if (!_mana || !_hp)
	{
		ECHO(" is unable to repair itself!");
		return ;
	}
	_mana--;
	if (_hp + amount > UINT_MAX)
		_hp = UINT_MAX;
	else
		_hp += amount;
	ECHO(" repaired itself for " << amount << " health points!");
}

