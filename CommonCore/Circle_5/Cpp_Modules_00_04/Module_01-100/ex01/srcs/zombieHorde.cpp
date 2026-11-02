/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 10:48:17 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/08 13:44:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	if (N <= 0) return NULL;

	Zombie* horde;

	try
	{
		horde = new Zombie[N];
	}
	catch (std::bad_alloc &e)
	{
		std::cerr << "Failed to allocate memory for " << N << " zombies: "
			<< e.what() << std::endl;
		return NULL;
	}

	for (int i = 0; i < N; ++i)
		horde[i].setName(name);

	return horde;
}
