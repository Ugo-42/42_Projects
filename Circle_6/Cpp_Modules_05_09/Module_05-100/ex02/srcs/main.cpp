/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/08 12:55:50 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main(void)
{
	ECHO(rgb(150, 0, 0)("——————————————————————————————————————"));

	{
		TITLE("Creating Bureaucrats and Forms");
		Bureaucrat	bureaucrat1("Alice", 1);
		Bureaucrat	bureaucrat2("Bob", 150);
		AForm		*shrubberyForm = new ShrubberyCreationForm("Home");
		AForm		*robotomyForm = new RobotomyRequestForm("Bender");
		AForm		*presidentialForm = new PresidentialPardonForm("Marvin");

		TITLE("Signing Forms");
		bureaucrat2.signForm(*shrubberyForm);
		bureaucrat1.signForm(*shrubberyForm);
		bureaucrat1.signForm(*robotomyForm);
		bureaucrat1.signForm(*presidentialForm);
		bureaucrat2.signForm(*presidentialForm);

		TITLE(bureaucrat2.getName() + " Executing Forms");
		bureaucrat2.executeForm(*presidentialForm);
		bureaucrat2.executeForm(*shrubberyForm);
		bureaucrat2.executeForm(*robotomyForm);

		TITLE(bureaucrat1.getName() + " Executing Forms");
		bureaucrat1.executeForm(*presidentialForm);
		bureaucrat1.executeForm(*shrubberyForm);
		bureaucrat1.executeForm(*robotomyForm);

		TITLE("Attempting to Execute Unsigned Form");
		AForm	*unsignedForm = new ShrubberyCreationForm("Garden");
		bureaucrat1.executeForm(*unsignedForm);

		TITLE("Cleaning Up");
		delete unsignedForm;
		delete shrubberyForm;
		delete robotomyForm;
		delete presidentialForm;
	}

    ECHO(rgb(150,0,0)("——————————————————————————————————————"));

	return 0;
}
