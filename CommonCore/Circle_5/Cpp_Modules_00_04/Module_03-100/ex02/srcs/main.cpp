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
			ECHO(TITLE("ClapTrap"));
			ClapTrap clap("Clappy");
			clap.attack("TargetA");
		}

		{
			ECHO(TITLE("ScavTrap"));
			ScavTrap scav("Scavvy");
			scav.attack("TargetB");
			scav.guardGate();
		}

		{
			ECHO(TITLE("FragTrap Test"));
			FragTrap frag("Fraggy");
			frag.attack("TargetC");
			frag.highFivesGuys();
			ECHO("");

			FragTrap copyFrag(frag);
			copyFrag.attack("CopyTarget");
			copyFrag.highFivesGuys();
			ECHO("");

			FragTrap assignedFrag("Temporary");
			assignedFrag = frag;
			assignedFrag.attack("AssignedTarget");
			assignedFrag.highFivesGuys();
		}
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
