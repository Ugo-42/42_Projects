/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:32:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/20 10:07:55 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                             Constructors                                   */
/* ************************************************************************** */


WrongAnimal::WrongAnimal()
{
	LOG(hex(0x6ca642) + "Default WrongAnimal constructor called" + RESET);
	_type = "WrongAnimal";
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) : _type(other._type)
{
	LOG(hex(0x6ca642) + "WrongAnimal Copy constructor called" + RESET);
	_type = "WrongAnimal";
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	if (this != &other)
		_type = other._type;
	return *this;
}


/* ************************************************************************** */
/*                             Destructors                                    */
/* ************************************************************************** */


WrongAnimal::~WrongAnimal()
{
	LOG(hex(0xc23030) + "WrongAnimal Destructor called" + RESET);
}


/* ************************************************************************** */
/*                              Functions                                     */
/* ************************************************************************** */


t_string WrongAnimal::getType() const
{
	return _type;
}

void WrongAnimal::makeSound() const
{
	ECHO(ITALIC "*general wrong animal sounds*" RESET);
}


