/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 12:01:33 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/10 10:50:55 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>

/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137)
	, _target("Default") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137)
	, _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other)
	, _target(other._target) {}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


ShrubberyCreationForm::~ShrubberyCreationForm() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


ShrubberyCreationForm	&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
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

#define B "\033[30m" // Black
#define G "\033[32m" // Green
#define Y "\033[33m" // Yellow

void	ShrubberyCreationForm::action() const
{
	std::ofstream	file((_target + "_shrubbery").c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("Error: Could not create file " + _target + "_shrubbery" + "!");
		return ;
	}
	file << B ".      " G "_-_\n"
			"    /~~   ~~\\\n"
			" /~~         ~~\\\n"
			"{               }\n"
			" \\  _-     -_  /\n"
			"   ~  " Y "\\\\ //  " G "~\n"
			"_- -   " Y "| | " G "_- _\n"
			"  _ -  " Y "| |   " G "-_\n"
			"      " Y "// \\\\ \n" RESET;
	file.close();
}

