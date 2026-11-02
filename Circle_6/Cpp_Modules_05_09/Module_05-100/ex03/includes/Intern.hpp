/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:03:38 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/10 15:03:45 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
	public:
		Intern();
		Intern(const Intern &other);
		~Intern();

		Intern				&operator=(const Intern &other);

		AForm				*makeForm(const std::string &formName, const std::string &target) const;

		class UnknownFormException : public std::exception
		{
			private:
				std::string _msg;
			public:
				UnknownFormException(const std::string &formName);
				~UnknownFormException() noexcept;
				const char *what() const noexcept;
		};
};
