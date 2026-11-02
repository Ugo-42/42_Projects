/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/04 12:07:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#define TITLE(x) BOLD << rgb(255,155,55) << "\n--- " << x << " ---" << RESET

int main( void )
{
	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		ECHO(TITLE("ScavTrap"));
		ScavTrap c("Segfault");

		c.attack("norminette");
		c.takeDamage(99);
		c.beRepaired(424242);
		c.takeDamage(99999);
		c.guardGate();

		ECHO(TITLE("ScavTrap Copy Constructor"));
		ScavTrap copy_c(c);
		copy_c.attack("Bus Error");

		ECHO(TITLE("ScavTrap Assignement Operator"));
		ScavTrap assigned("/dev/null");
		assigned = c;
		assigned.attack("Minishell");

		ECHO(TITLE("Polymorphism"));
		ClapTrap *ptr = &c;
		ptr->attack("Polymorphic");

		ClapTrap &ref = c;
		ref.attack("PolymorphicRef");

		ECHO(TITLE("Basic ClapTrap"));
		ClapTrap basic("Clappy");
		basic.attack("Segfault");
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
