/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/08 13:01:25 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Bureaucrat.hpp"
#include "AForm.hpp"


/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


Bureaucrat::Bureaucrat()
	: _name("Default")
	, _grade(150) {}

Bureaucrat::Bureaucrat(const std::string &name, int grade)
	: _name(name)
{
	if (grade < 1)
		throw GradeTooHighException(_name);
	else if (grade > 150)
		throw GradeTooLowException(_name);
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: _name(other._name)
	, _grade(other._grade) {}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


Bureaucrat::~Bureaucrat() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
		_grade = other._grade;
	return *this;
}

std::ostream &operator<<(std::ostream &o, const Bureaucrat &b)
{
	o << b.getName() << ", bureaucrat grade " << b.getGrade();
	return o;
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


const std::string &Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
{
	return _grade;
}

void Bureaucrat::incrementGrade()
{
	if (_grade <= 1)
		throw GradeTooHighException(_name);
	_grade--;
}

void Bureaucrat::decrementGrade()
{
	if (_grade >= 150)
		throw GradeTooLowException(_name);
	_grade++;
}

void Bureaucrat::signForm(class AForm &form)
{
	if (form.isSigned())
	{
		ECHO(rgb(255, 255, 0)("Warning: " + I(form.getName()) + " is already signed!"));
		return ;
	}

	try
	{
		form.beSigned(*this);
		ECHO(rgb(75,255,75)(_name + " signed " + I(form.getName()) + "."));
	}
	catch (std::exception &e)
	{
		ECHO(rgb(255,25,25)(_name + " couldn't sign " + I(form.getName()) + ": " + e.what()));
	}
}

void Bureaucrat::executeForm(const class AForm &form) const
{
	try
	{
		form.execute(*this);
		ECHO(rgb(75,255,75)(_name + " executed " + I(form.getName()) + "."));
	}
	catch (std::exception &e)
	{
		ECHO(rgb(255,25,25)("Error: " + t_string(e.what())));
	}
}

/* ************************************************************************** */
/*                                 Exceptions                                 */
/* ************************************************************************** */

/* ============================== Constructors ============================== */

Bureaucrat::GradeTooHighException::GradeTooHighException(const std::string &name)
	: _msg(rgb(255,25,25)("Grade is too high for " + I(name) + "!")) {}

Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string &name)
	: _msg(rgb(255,25,25)("Grade is too low for " + I(name) + "!")) {}

/* ================================ Methods ================================= */

const char *Bureaucrat::GradeTooHighException::what() const noexcept
{
	return _msg.c_str();
}

const char *Bureaucrat::GradeTooLowException::what() const noexcept
{
	return _msg.c_str();
}

/* =============================== Destructors =============================== */

Bureaucrat::GradeTooHighException::~GradeTooHighException() noexcept {}

Bureaucrat::GradeTooLowException::~GradeTooLowException() noexcept {}


