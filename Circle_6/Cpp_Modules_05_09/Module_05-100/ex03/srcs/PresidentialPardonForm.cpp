/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:02:24 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/09 12:02:35 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", 25, 5)
	, _target("Default") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
	: AForm("PresidentialPardonForm", 25, 5)
	, _target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
	: AForm(other)
	, _target(other._target) {}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


PresidentialPardonForm::~PresidentialPardonForm() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


PresidentialPardonForm	&PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		_target = other._target;
	}
	return (*this);
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


void	PresidentialPardonForm::action() const
{
	ECHO(rgb(125,125,200)(I(_target + " has been pardoned by Zaphod Beeblebrox.")));
}
