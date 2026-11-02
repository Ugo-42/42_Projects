/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 11:49:27 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 11:49:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */

MateriaSource::MateriaSource()
{
	LOG(rgb(0,200,0) << "MateriaSource Default Constructor called" << RESET);
	for (int i = 0; i < 4; ++i)
		_templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &other)
{
	LOG(rgb(0,200,0) << "MateriaSource Copy Constructor called" << RESET);
	for (int i = 0; i < 4; ++i)
	{
		if (other._templates[i])
			_templates[i] = other._templates[i]->clone();
		else
			_templates[i] = NULL;
	}
}

/* ************************************************************************** */
/*                                Destructor                                  */
/* ************************************************************************** */

MateriaSource::~MateriaSource()
{
	LOG(rgb(200,0,0) <<"MateriaSource Destructor called" << RESET);
	for (int i = 0; i < 4; ++i)
	{
		if (_templates[i])
			delete _templates[i];
	}
}

/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	LOG(rgb(255,155,0) << "MateriaSource Assignment Operator called" << RESET);
	if (this != &other)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (_templates[i])
				delete _templates[i];
			if (other._templates[i])
				_templates[i] = other._templates[i]->clone();
			else
				_templates[i] = NULL;
		}
	}
	return (*this);
}

/* ************************************************************************** */
/*                             Member Functions                               */
/* ************************************************************************** */

void MateriaSource::learnMateria(AMateria *m)
{
	if (!m)
	{
		ECHO("MateriaSource cannot learn NULL materia!");
		return;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (!_templates[i])
		{
			_templates[i] = m;
			ECHO("MateriaSource learned materia of type: " << m->getType());
			return;
		}
	}
	ECHO("MateriaSource cannot learn more materia, inventory full!");
	ECHO("Throwing this materia!");
	delete m;
}

AMateria *MateriaSource::createMateria(const t_string &type)
{
	for (int i = 0; i < 4; ++i)
	{
		if (_templates[i] && _templates[i]->getType() == type)
		{
			ECHO("MateriaSource creating materia of type: " << type);
			return (_templates[i]->clone());
		}
	}
	ECHO("MateriaSource cannot create materia of type: " << type << ", not learned!");
	return (NULL);
}
