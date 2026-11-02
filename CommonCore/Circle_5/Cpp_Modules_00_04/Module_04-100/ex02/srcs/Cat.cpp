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


Cat::Cat()
{
	LOG(hex(0x6ca642) + "Default Cat constructor called" + RESET);
	_type = "Cat";
	_brain = new Brain();
}

Cat::Cat(const Cat& other) : Animal(other)
{
	LOG(hex(0x6ca642) + "Cat Copy constructor called" + RESET);
	_type = "Cat";
	_brain = new Brain(*other._brain);
}

Cat& Cat::operator=(const Cat& other)
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


Cat::~Cat()
{
	LOG(hex(0xc23030) + "Cat Destructor called" + RESET);
	delete _brain;
}


/* ************************************************************************** */
/*                              Functions                                     */
/* ************************************************************************** */


void Cat::makeSound() const
{
	ECHO(ITALIC "*meow meow*" RESET);
}

Brain* Cat::getBrain() const
{
	return _brain;
}


