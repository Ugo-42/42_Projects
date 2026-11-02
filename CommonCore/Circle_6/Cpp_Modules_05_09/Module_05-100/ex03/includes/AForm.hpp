/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:18:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/28 10:19:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bureaucrat.hpp"

class AForm
{
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_signGrade;
		const int			_executeGrade;

	protected:
		virtual void		action() const = 0;

	public:
		AForm();
		AForm(const std::string &name, int signGrade, int executeGrade);
		AForm(const AForm &other);
		virtual ~AForm();

		AForm				&operator=(const AForm &other);

		const std::string	&getName() const;
		bool				isSigned() const;
		int					getSignGrade() const;
		int					getExecuteGrade() const;
		void				beSigned(const Bureaucrat &b);

		virtual void		execute(const Bureaucrat &executor) const;
		

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
		class FormNotSignedException : public std::exception
		{
			private:
				std::string _msg;
			public:
				FormNotSignedException(const std::string &name);
				~FormNotSignedException() noexcept;
				const char *what() const noexcept;
		};
};

std::ostream	&operator<<(std::ostream &o, const AForm &f);
