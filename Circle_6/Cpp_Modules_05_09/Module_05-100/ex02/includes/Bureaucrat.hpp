/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/08 13:01:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "config.hpp"
#include <stdexcept>
#include <string>

class Bureaucrat
{
	private:
		std::string const   _name;
		int                 _grade;

	public:
		Bureaucrat();
		Bureaucrat(const std::string &name, int grade);
		Bureaucrat(const Bureaucrat &src);
		~Bureaucrat();

		Bureaucrat          &operator=(const Bureaucrat &other);

		const std::string   &getName() const;
		int                 getGrade() const;
		void                incrementGrade();
		void                decrementGrade();

		void                signForm(class AForm &form);
		void                executeForm(const class AForm &form) const;

		class GradeTooHighException : public std::exception
		{
			private:
				std::string _msg;
			public:
				GradeTooHighException(const std::string &name);
				~GradeTooHighException() noexcept;
				const char *what() const noexcept;
		};
		class GradeTooLowException : public std::exception
		{
			private:
				std::string _msg;
			public:
				GradeTooLowException(const std::string &name);
				~GradeTooLowException() noexcept;
				const char *what() const noexcept;
		};
};

std::ostream    &operator<<(std::ostream &o, const Bureaucrat &b);
