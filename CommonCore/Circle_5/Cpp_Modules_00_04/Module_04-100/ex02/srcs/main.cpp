/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 09:54:33 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#define YES 0

int main(void)
{
    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		Animal *a = new Dog();
		Animal *b = new Cat();

		ECHO(a->getType());
		ECHO(b->getType());

		delete a;
		delete b;

		#if YES
			Animal *c = new Animal();

			ECHO(c->getType());
			delete c;
		#endif
	}

    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

    return 0;
}
