/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/28 10:19:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Form.hpp"


/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


Form::Form()
	: _name("Default")
	, _isSigned(false)
	, _signGrade(150)
	, _executeGrade(150) {}

Form::Form(const std::string &name, int signGrade, int executeGrade)
	: _name(name)
	, _isSigned(false)
	, _signGrade(signGrade)
	, _executeGrade(executeGrade)
{
	if (signGrade < 1 || executeGrade < 1)
		throw Form::GradeTooHighException(_name);
	if (signGrade > 150 || executeGrade > 150)
		throw Form::GradeTooLowException(_name);
}

Form::Form(const Form &other)
	: _name(other._name)
	, _isSigned(other._isSigned)
	, _signGrade(other._signGrade)
	, _executeGrade(other._executeGrade) {}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


Form::~Form() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


Form	&Form::operator=(const Form &other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return (*this);
}

std::ostream	&operator<<(std::ostream &o, const Form &f)
{
	o << "Form " << I(f.getName()) << ", Sign Grade: " << f.getSignGrade()
	  << ", Execute Grade: " << f.getExecuteGrade()
	  << ", Signed: " << (f.isSigned() ? "✅" : "❌");
	return (o);
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


void	Form::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > _signGrade)
		throw Form::GradeTooLowException(_name);
	_isSigned = true;
}

std::string	const &Form::getName() const
{
	return (_name);
}

bool	Form::isSigned() const
{
	return (_isSigned);
}

int	Form::getSignGrade() const
{
	return (_signGrade);
}

int	Form::getExecuteGrade() const
{
	return (_executeGrade);
}


/* ************************************************************************** */
/*                                 Exceptions                                 */
/* ************************************************************************** */


/* ============================== Constructors ============================== */

Form::GradeTooHighException::GradeTooHighException(const std::string &name)
	: _msg(rgb(255,25,25)("Grade is too high for " + I(name) + "!")) {}

Form::GradeTooLowException::GradeTooLowException(const std::string &name)
	: _msg(rgb(255,25,25)("Grade is too low for " + I(name) + "!")) {}

/* ================================ Methods ================================= */

const char	*Form::GradeTooHighException::what() const noexcept
{
	return (_msg.c_str());
}

const char	*Form::GradeTooLowException::what() const noexcept
{
	return (_msg.c_str());
}

/* ============================== Destructors =============================== */

Form::GradeTooHighException::~GradeTooHighException() noexcept {}

Form::GradeTooLowException::~GradeTooLowException() noexcept {}

