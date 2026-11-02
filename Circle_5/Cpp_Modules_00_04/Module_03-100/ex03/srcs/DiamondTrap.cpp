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


DiamondTrap::DiamondTrap() : ClapTrap("DiamondTrap" "_clap_name")
{
	_name = "Default";
	_hp = FragTrap::_hp;
	_mana = ScavTrap::_mana;
	_dmg = FragTrap::_dmg;
	LOG(hex(0x6ca642) + "Default DiamondTrap constructor called" + RESET);
}

DiamondTrap::DiamondTrap(const t_string& name) : ClapTrap(name + "_clap_name")
{
	_name = name;
	_hp = FragTrap::_hp;
	_mana = ScavTrap::_mana;
	_dmg = FragTrap::_dmg;
	LOG(hex(0x6ca642) + "DiamondTrap Name constructor called" + RESET);
}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */

DiamondTrap::~DiamondTrap()
{
	LOG(hex(0xc23030) + "DiamondTrap Destructor called" + RESET);
}


/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */


void DiamondTrap::attack(const t_string& target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI()
{
	ECHO("I am " << _name << " and my ClapTrap name is " << ClapTrap::_name);
}
