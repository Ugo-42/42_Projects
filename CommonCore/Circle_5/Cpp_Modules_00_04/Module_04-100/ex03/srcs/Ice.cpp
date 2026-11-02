/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:13:01 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 11:13:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */

Ice::Ice() : AMateria("ice")
{
	LOG(rgb(0,200,0) << "Ice Default Constructor called" << RESET);
}

Ice::Ice(const Ice &other) : AMateria("ice")
{
	(void)other;
	LOG(rgb(0,200,0) << "Ice Copy Constructor called" << RESET);
}

/* ************************************************************************** */
/*                                Destructor                                  */
/* ************************************************************************** */

Ice::~Ice()
{
	LOG(rgb(200,0,0) << "Ice Destructor called" << RESET);
}

/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */

Ice &Ice::operator=(const Ice &other)
{
	LOG(rgb(255,155,0) << "Ice Assignment Operator called" << RESET);
	(void)other;
	return (*this);
}

/* ************************************************************************** */
/*                             Member Functions                               */
/* ************************************************************************** */

AMateria *Ice::clone() const
{
	return (new Ice(*this));
}

void Ice::use(ICharacter &target)
{
	ECHO(ITALIC << "* shoots an ice bolt at " << target.getName() << " *" << RESET);
}


