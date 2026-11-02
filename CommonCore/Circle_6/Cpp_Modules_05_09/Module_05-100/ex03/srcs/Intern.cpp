/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:07:16 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/10 15:07:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


Intern::Intern() {}

Intern::Intern(const Intern &other) { (void)other; }


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


Intern::~Intern() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


Intern	&Intern::operator=(const Intern &other)
{
	(void)other;
	return (*this);
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


/* ================================ Helpers ================================= */
static AForm	*createShrubberyForm(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}

static AForm	*createRobotomyForm(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}

static AForm	*createPresidentialForm(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}
/* ========================================================================== */

AForm	*Intern::makeForm(const std::string &formName, const std::string &target) const
{
	const std::string	formNames[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};
	AForm * (*forms[3])(const std::string &target) = {
		createShrubberyForm,
		createRobotomyForm,
		createPresidentialForm
	};

	for (size_t i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << " form." << std::endl;
			return (forms[i](target));
		}
	}

	throw Intern::UnknownFormException(formName);
}


/* ************************************************************************** */
/*                                 Exceptions                                 */
/* ************************************************************************** */

/* ============================== Constructors ============================== */
Intern::UnknownFormException::UnknownFormException(const std::string &formName)
	: _msg("Error: Unknown form name '" + formName + "'!") {}

/* ================================ Methods ================================= */
const char	*Intern::UnknownFormException::what() const noexcept
{
	return (_msg.c_str());
}

/* ============================== Destructors =============================== */
Intern::UnknownFormException::~UnknownFormException() noexcept {}
