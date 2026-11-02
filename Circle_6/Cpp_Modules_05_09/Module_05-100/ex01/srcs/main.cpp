/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/03 11:48:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

static void invalidFormCreationTest(const std::string &name,
	int signGrade, int executeGrade)
{
	try
	{
		Form formC(name, signGrade, executeGrade);
	}
	catch (std::exception &e)
	{
		ERROR(rgb(255,25,25)("Error creating form " + I(name)
				+ ": " + t_string(e.what())));
	}
}

int main(void)
{
	ECHO(rgb(150, 0, 0)("——————————————————————————————————————"));

	{
		TITLE("Form Creation");

		Form formA("Avocado", 50, 100);
		Form formB("Banana", 1, 100);

		ECHO(formA);
		ECHO(formB);

		TITLE("Bureaucrat Signing Forms");

		Bureaucrat bob("Bob", 75);
		Bureaucrat alice("Alice", 25);

		ECHO(bob);
		ECHO(alice);

		bob.signForm(formA);
		bob.signForm(formB);
		alice.signForm(formA);
		alice.signForm(formB);

		ECHO(formA);
		ECHO(formB);

		TITLE("Already Signed Form");

		alice.signForm(formA);

		ECHO(formA);

		TITLE("Invalid Form Creation");

		invalidFormCreationTest("Cherry", 0, 100);
		invalidFormCreationTest("Date", 151, 100);
		invalidFormCreationTest("Elderberry", 50, 0);
		invalidFormCreationTest("Fig", 50, 151);

	}

    ECHO(rgb(150,0,0)("——————————————————————————————————————"));

	return 0;
}
