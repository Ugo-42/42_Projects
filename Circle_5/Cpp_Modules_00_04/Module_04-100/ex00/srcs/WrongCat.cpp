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


WrongCat::WrongCat()
{
	LOG(hex(0x6ca642) + "Default WrongCat constructor called" + RESET);
	_type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	LOG(hex(0x6ca642) + "WrongCat Copy constructor called" + RESET);
	_type = "WrongCat";
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	if (this != &other)
		_type = other._type;
	return *this;
}


/* ************************************************************************** */
/*                             Destructors                                    */
/* ************************************************************************** */


WrongCat::~WrongCat()
{
	LOG(hex(0xc23030) + "WrongCat Destructor called" + RESET);
}


/* ************************************************************************** */
/*                              Functions                                     */
/* ************************************************************************** */


void WrongCat::makeSound() const
{
	ECHO(ITALIC "*woem woem*" RESET);
}


