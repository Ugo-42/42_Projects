/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/08 13:47:52 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main( void )
{
	int const N = 42;
	t_string const name = "HordeZombie";

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	Zombie* horde = zombieHorde(N, name);
	if (!horde)
		return 1;

	for (int i = 0; i < N; ++i)
		horde[i].announce();

	ECHO("\n   🧟 🧟 🧟🪦   🧟 🪦 🪦 🧟  🧟  ");
	ECHO("  \033[38;5;130;53m                               " RESET);

	delete[] horde;

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}

