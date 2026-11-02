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


Dog::Dog()
{
	LOG(hex(0x6ca642) + "Default Dog constructor called" + RESET);
	_type = "Dog";
	_brain = new Brain();
}

Dog::Dog(const Dog& other) : Animal(other)
{
	LOG(hex(0x6ca642) + "Dog Copy constructor called" + RESET);
	_type = "Dog";
	_brain = new Brain(*other._brain);
}

Dog& Dog::operator=(const Dog& other)
{
	if (this != &other)
	{
		_type = other._type;
		*_brain = *other._brain;
	}
	return *this;
}


/* ************************************************************************** */
/*                             Destructors                                    */
/* ************************************************************************** */


Dog::~Dog()
{
	LOG(hex(0xc23030) + "Dog Destructor called" + RESET);
	delete _brain;
}


/* ************************************************************************** */
/*                              Functions                                     */
/* ************************************************************************** */


void Dog::makeSound() const
{
	ECHO(ITALIC "*woof woof*" RESET);
}

Brain* Dog::getBrain() const
{
	return _brain;
}
