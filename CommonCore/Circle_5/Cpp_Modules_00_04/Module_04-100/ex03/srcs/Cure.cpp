/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:35:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 11:35:40 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */

Cure::Cure() : AMateria("cure")
{
	LOG(rgb(0,200,0) << "Cure Default Constructor called" << RESET);
}

Cure::Cure(const Cure &other) : AMateria("cure")
{
	(void)other;
	LOG(rgb(0,200,0) << "Cure Copy Constructor called" << RESET);
}

/* ************************************************************************** */
/*                                Destructor                                  */
/* ************************************************************************** */

Cure::~Cure()
{
	LOG(rgb(200,0,0) << "Cure Destructor called" << RESET);
}

/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */

Cure &Cure::operator=(const Cure &other)
{
	LOG(rgb(255,155,0) << "Cure Assignment Operator called" << RESET);
	(void)other;
	return (*this);
}

/* ************************************************************************** */
/*                             Member Functions                               */
/* ************************************************************************** */

AMateria *Cure::clone() const
{
	return (new Cure(*this));
}

void Cure::use(ICharacter &target)
{
	ECHO(ITALIC << "* heals " << target.getName() << "'s wounds *" << RESET);
}



