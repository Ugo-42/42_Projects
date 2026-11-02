/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/08 13:05:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "AForm.hpp"


/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


AForm::AForm()
	: _name("Default")
	, _isSigned(false)
	, _signGrade(150)
	, _executeGrade(150) {}

AForm::AForm(const std::string &name, int signGrade, int executeGrade)
	: _name(name)
	, _isSigned(false)
	, _signGrade(signGrade)
	, _executeGrade(executeGrade)
{
	if (signGrade < 1 || executeGrade < 1)
		throw AForm::GradeTooHighException(_name);
	if (signGrade > 150 || executeGrade > 150)
		throw AForm::GradeTooLowException(_name);
}

AForm::AForm(const AForm &other)
	: _name(other._name)
	, _isSigned(other._isSigned)
	, _signGrade(other._signGrade)
	, _executeGrade(other._executeGrade) {}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


AForm::~AForm() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


AForm	&AForm::operator=(const AForm &other)
{
	if (this != &other)
		_isSigned = other._isSigned;
	return (*this);
}

std::ostream	&operator<<(std::ostream &o, const AForm &f)
{
	o << "AForm " << I(f.getName()) << ", Sign Grade: " << f.getSignGrade()
	  << ", Execute Grade: " << f.getExecuteGrade()
	  << ", Signed: " << (f.isSigned() ? "✅" : "❌");
	return (o);
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


void	AForm::beSigned(const Bureaucrat &b)
{
	if (b.getGrade() > _signGrade)
		throw AForm::GradeTooLowException(_name);
	_isSigned = true;
}

std::string	const &AForm::getName() const
{
	return (_name);
}

bool	AForm::isSigned() const
{
	return (_isSigned);
}

int	AForm::getSignGrade() const
{
	return (_signGrade);
}

int	AForm::getExecuteGrade() const
{
	return (_executeGrade);
}

void	AForm::execute(const Bureaucrat &executor) const
{
	if (!_isSigned)
		throw AForm::FormNotSignedException(_name);
	if (executor.getGrade() > _executeGrade)
		throw AForm::GradeTooLowException(executor.getName());
	action();
}


/* ************************************************************************** */
/*                                 Exceptions                                 */
/* ************************************************************************** */


/* ============================== Constructors ============================== */

AForm::GradeTooHighException::GradeTooHighException(const std::string &name)
	: _msg(rgb(255,25,25)("Grade is too high for " + I(name) + "!")) {}

AForm::GradeTooLowException::GradeTooLowException(const std::string &name)
	: _msg(rgb(255,25,25)("Grade is too low for " + I(name) + "!")) {}

AForm::FormNotSignedException::FormNotSignedException(const std::string &name)
	: _msg(rgb(255,25,25)(I(name) + " is not signed!")) {}

/* ================================ Methods ================================= */

const char	*AForm::GradeTooHighException::what() const noexcept
{
	return (_msg.c_str());
}

const char	*AForm::GradeTooLowException::what() const noexcept
{
	return (_msg.c_str());
}

const char	*AForm::FormNotSignedException::what() const noexcept
{
	return (_msg.c_str());
}

/* ============================== Destructors =============================== */

AForm::GradeTooHighException::~GradeTooHighException() noexcept {}

AForm::GradeTooLowException::~GradeTooLowException() noexcept {}

AForm::FormNotSignedException::~FormNotSignedException() noexcept {}

