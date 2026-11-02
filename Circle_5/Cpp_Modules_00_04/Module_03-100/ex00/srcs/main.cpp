/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/06 15:12:05 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#define TITLE(x) BOLD << rgb(255,155,55) << "\n--- " << x << " ---" << RESET

int main( void )
{
	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		ECHO(TITLE("ClapTrap Test"));
		ClapTrap c("Segfault");

		c.attack("norminette");
		c.attack("moulinette");
		c.attack("deepthought");
		c.takeDamage(9999999);
		c.beRepaired(424242);
		c.attack("examshell");

		ECHO("");
		ClapTrap d("Bus Error");

		d.attack("Minishell");
		d.takeDamage(3);
		d.beRepaired(424242);
		d.attack("Inception");

		ECHO(TITLE("ClapTrap Assignement Operator"));
		ClapTrap e("NULL");
		e = d;
		e.attack("Segfault");

		ECHO(TITLE("ClapTrap Copy Constructor"));
		ClapTrap f(e);
		f.takeDamage(420007);
		f.attack("Bus Error");
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
