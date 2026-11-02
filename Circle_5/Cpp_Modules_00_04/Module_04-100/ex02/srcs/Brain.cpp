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


Brain::Brain()
{
	LOG(hex(0x6ca642) + "Default Brain constructor called" + RESET);
}

Brain::Brain(const Brain& other)
{
	LOG(hex(0x6ca642) + "Brain Copy constructor called" + RESET);
	for (int i = 0; i < 100; ++i)
	{
		_ideas[i] = other._ideas[i];
	}
}

Brain& Brain::operator=(const Brain& other)
{
	LOG(hex(0x6ca642) + "Brain Copy assignment operator called" + RESET);
	if (this != &other)
	{
		for (int i = 0; i < 100; ++i)
		{
			_ideas[i] = other._ideas[i];
		}
	}
	return (*this);
}


/* ************************************************************************** */
/*                             Destructors                                    */
/* ************************************************************************** */


Brain::~Brain()
{
	LOG(hex(0xc23030) + "Brain Destructor called" + RESET);
}


/* ************************************************************************** */
/*                           Member functions                                 */
/* ************************************************************************** */


void Brain::setIdea(int index, const t_string& idea)
{
	if (index >= 0 && index < 100)
	{
		_ideas[index] = idea;
	}
}

t_string Brain::getIdea(int index) const
{
	if (index >= 0 && index < 100)
	{
		return _ideas[index];
	}
	return "";
}
