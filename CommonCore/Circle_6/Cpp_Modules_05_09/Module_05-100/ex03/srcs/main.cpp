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
		TITLE ("Creating Bureaucrats");

		Bureaucrat	bureaucrat1("Alice", 1);
		Bureaucrat	bureaucrat2("Bob", 150);

		ECHO(bureaucrat1);
		ECHO(bureaucrat2);

		TITLE("Testing Interns");

		Intern	someRandomIntern;
		AForm	*rrf;
		AForm	*scf;
		AForm	*ppf;

		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		scf = someRandomIntern.makeForm("shrubbery creation", "Home");
		ppf = someRandomIntern.makeForm("presidential pardon", "Marvin");

		NEW_LINE;

		ECHO(*rrf);
		ECHO(*scf);
		ECHO(*ppf);

		TITLE("Signing Forms");
		bureaucrat1.signForm(*rrf);
		bureaucrat2.signForm(*scf);
		bureaucrat1.signForm(*ppf);

		TITLE("Executing Forms");
		bureaucrat2.executeForm(*rrf);
		bureaucrat1.executeForm(*scf);
		bureaucrat1.executeForm(*ppf);

		TITLE("Cleaning Up");
		delete rrf;
		delete scf;
		delete ppf;
	}

    ECHO(rgb(150,0,0)("——————————————————————————————————————"));

	return 0;
}
