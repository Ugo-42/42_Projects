/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:32:50 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/10 13:29:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                             Constructors                                   */
/* ************************************************************************** */


Animal::Animal()
{
	LOG(hex(0x6ca642) + "Default Animal constructor called" + RESET);
	_type = "Animal";
}

Animal::Animal(const Animal& other) : _type(other._type)
{
	LOG(hex(0x6ca642) + "Animal Copy constructor called" + RESET);
	_type = "Animal";
}

Animal& Animal::operator=(const Animal& other)
{
	LOG(hex(0xff9900) + "Animal Copy assignment operator called" + RESET);
	if (this != &other)
		_type = other._type;
	return *this;
}


/* ************************************************************************** */
/*                             Destructors                                    */
/* ************************************************************************** */


Animal::~Animal()
{
	LOG(hex(0xc23030) + "Animal Destructor called" + RESET);
}


/* ************************************************************************** */
/*                              Functions                                     */
/* ************************************************************************** */


t_string Animal::getType() const
{
	return _type;
}

void Animal::makeSound() const
{
	ECHO(ITALIC "*general animal sounds*" RESET);
}


