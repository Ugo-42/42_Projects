/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Amateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:36:42 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 11:36:50 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */

AMateria::AMateria() : _type("default")
{
	LOG(rgb(0,200,0) << "AMateria Default Constructor called" << RESET);
}

AMateria::AMateria(const AMateria &other)
{
	(void)other;
	LOG(rgb(0,200,0) << "AMateria Copy Constructor called" << RESET);
}

AMateria::AMateria(const t_string &type) : _type(type)
{
	LOG(rgb(0,200,0) << "AMateria Type Constructor called" << RESET);
}

/* ************************************************************************** */
/*                                Destructor                                  */
/* ************************************************************************** */

AMateria::~AMateria()
{
	LOG(rgb(200,0,0) << "AMateria Destructor called" << RESET);
}

/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */

AMateria &AMateria::operator=(const AMateria &other)
{
	LOG(rgb(255,155,0) << "AMateria Assignment Operator called" << RESET);
	(void)other;
	return (*this);
}

/* ************************************************************************** */
/*                             Member Functions                               */
/* ************************************************************************** */

const t_string &AMateria::getType() const
{
	return (_type);
}

void AMateria::use(ICharacter &target)
{
	ECHO("AMateria used on " << target.getName());
}

