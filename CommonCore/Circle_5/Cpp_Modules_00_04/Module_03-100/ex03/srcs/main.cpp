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
		{
			ECHO(TITLE("Basic ClapTrap Test"));
			ClapTrap clap("Clappy");
			clap.attack("BasicTarget");
			clap.takeDamage(5);
			clap.beRepaired(2);
		}

		{
			ECHO(TITLE("Basic ScavTrap Test"));
			ScavTrap scav("Scavvy");
			scav.attack("ScavTarget");
			scav.guardGate();
		}

		{
			ECHO(TITLE("Basic FragTrap Test"));
			FragTrap frag("Fraggy");
			frag.attack("FragTarget");
			frag.highFivesGuys();
		}

		ECHO(TITLE("DiamondTrap Creation + Special Abilities"));
		{
			DiamondTrap dia("DiamondBoy");

			dia.attack("DiamondTarget");
			dia.highFivesGuys();
			dia.guardGate();
			dia.whoAmI();
		}

		ECHO(TITLE("DiamondTrap Copy Constructor"));
		{
			DiamondTrap original("Original");
			original.attack("BeforeCopy");
			original.whoAmI();

			DiamondTrap copy(original);

			copy.attack("CopyAttack");
			copy.whoAmI();
		}

		ECHO(TITLE("DiamondTrap Copy Assignment Operator"));
		{
			DiamondTrap a("AssignA");
			DiamondTrap b("AssignB");

			a.whoAmI();
			b.whoAmI();

			b = a;

			b.attack("AssignedAttack");
			b.whoAmI();
		}
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
