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

static void testBureaucrat(const std::string &name, int grade)
{
	try
	{
		Bureaucrat b(name, grade);
		ECHO(b);
	}
	catch (std::exception &e)
	{
		ERROR("Exception: " << e.what());
	}
}

int main(void)
{
    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		TITLE("Bureaucrat Creation Tests");

		testBureaucrat("The Rock", 42);
		testBureaucrat("Shrek", 1);

		TITLE("Grade too High/Low on Construction");

		testBureaucrat("Overflow", 2147483647);
		testBureaucrat("Aleph", 0);
		testBureaucrat("EXIT_FAILURE", -1);

		TITLE("Decrement Grade Tests");

		try
		{
			Bureaucrat c("Creeper", 149);
			ECHO(c);
			c.decrementGrade();
			ECHO(c);
			c.decrementGrade();
			ECHO(c);
		}
		catch (const std::exception &e)
		{
			ERROR("Exception: " << e.what());
		}

		TITLE("Increment Grade Tests");

		try
		{
			Bureaucrat d("Walter White", 1);
			ECHO(d);
			d.incrementGrade();
			ECHO(d);
		}
		catch (const std::exception &e)
		{
			ERROR("Exception: " << e.what());
		}
	}

    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

    return 0;
}
