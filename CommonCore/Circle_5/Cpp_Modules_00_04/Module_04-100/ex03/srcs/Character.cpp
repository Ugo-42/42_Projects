/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:38:28 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 11:38:35 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */

Character::Character() : _name("default"), _floorCount(0)
{
	LOG(rgb(0,200,0) << "Character Default Constructor called" << RESET);
	for (int i = 0; i < 4; ++i)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; ++i)
		_floor[i] = NULL;
}

Character::Character(const t_string &name) : _name(name), _floorCount(0)
{
	LOG(rgb(0,200,0) << "Character Name Constructor called" << RESET);
	for (int i = 0; i < 4; ++i)
		_inventory[i] = NULL;
	for (int i = 0; i < 100; ++i)
		_floor[i] = NULL;
}

Character::Character(const Character &other) : _name(other._name)
{
	LOG(rgb(0,200,0) << "Character Copy Constructor called" << RESET);
	_floorCount = 0;
	for (int i = 0; i < 100; ++i)
		_floor[i] = NULL;
	for (int i = 0; i < 4; ++i)
	{
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
}

/* ************************************************************************** */
/*                                Destructor                                  */
/* ************************************************************************** */

Character::~Character()
{
	LOG(rgb(200,0,0) << "Character Destructor called" << RESET);
	for (int i = 0; i < 4; ++i)
	{
		if (_inventory[i])
			delete _inventory[i];
	}
	for (int i = 0; i < _floorCount; ++i)
	{
		delete _floor[i];
	}
}

/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */

Character &Character::operator=(const Character &other)
{
	LOG(rgb(255,155,0) << "Character Assignment Operator called" << RESET);
	if (this != &other)
	{
		_name = other._name;
		_floorCount = 0;
		for (int i = 0; i < 100; ++i)
			_floor[i] = NULL;
		for (int i = 0; i < 4; ++i)
		{
			if (_inventory[i])
				delete _inventory[i];
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
			else
				_inventory[i] = NULL;
		}
	}
	return (*this);
}

/* ************************************************************************** */
/*                             Member Functions                               */
/* ************************************************************************** */

const t_string &Character::getName() const
{
	return (_name);
}

void Character::equip(AMateria *m)
{
	if (!m)
	{
		ECHO("Cannot equip a null Materia!");
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (_inventory[i] == NULL)
		{
			_inventory[i] = m;
			ECHO("Character " << _name << " equipped " << m->getType() << " in slot " << i);
			return;
		}
	}
	ECHO("Character " << _name << "'s inventory is full! Throwing " << m->getType() << " away!");
	delete m;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4)
	{
		ECHO("Character " << _name << " cannot unequip from invalid slot " << idx);
		return;
	}
	if (_inventory[idx] != NULL)
	{
		ECHO("Character " << _name << " unequipped " << _inventory[idx]->getType() << " from slot " << idx);
		if (_floorCount < 100)
			_floor[_floorCount++] = _inventory[idx];
		else
			clean_floor();
		_inventory[idx] = NULL;
	}
	else
	{
		ECHO("Character " << _name << "'s slot " << idx << " is already empty!");
	}
}

void Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= 4)
	{
		ECHO("Character " << _name << " cannot use from invalid slot " << idx);
		return;
	}
	if (_inventory[idx] != NULL)
	{
		ECHO("Character " << _name << " uses " << _inventory[idx]->getType() << " on " << target.getName());
		_inventory[idx]->use(target);
	}
	else
	{
		ECHO("Character " << _name << "'s slot " << idx << " is empty! Cannot use.");
	}
}

void Character::clean_floor()
{
	for (int i = 0; i < _floorCount; ++i)
	{
		delete _floor[i];
		_floor[i] = NULL;
	}
	_floorCount = 0;
}
