/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 09:49:17 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#define TITLE(x) "\n" << BOLD << rgb(255,155,55) << "--- " << x << " ---" << RESET

#define N 100

int main(void)
{
    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		Animal* Animals[100];

		ECHO(TITLE("Test " << N << " Animals"));
        for (int i = 0; i < N; ++i)
        {
            if (i % 2 == 0)
                Animals[i] = new Dog();
            else
                Animals[i] = new Cat();
        }

        for (int i = 0; i < N; ++i)
		{
            delete Animals[i];
		}
    }

    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		ECHO(TITLE("Testing deep copy"));

		Cat a;
		a.getBrain()->setIdea(0, "Throw your things on the floor 😼");
		a.getBrain()->setIdea(1, "Zzzz...");

		Cat b;
		
		b = a;
		ECHO('\n' + rgb(111,111,255) + "// CatB = CatA" + RESET);
		ECHO("CatA->Idea(0): " << a.getBrain()->getIdea(0));
		ECHO("CatA->Idea(1): " << a.getBrain()->getIdea(1));
		ECHO("CatB->Idea(0): " << b.getBrain()->getIdea(0));
		ECHO("CatB->Idea(1): " << b.getBrain()->getIdea(1));

		ECHO('\n' + rgb(111,111,255) + "// Changing CatB->Idea(0)" + RESET);
		b.getBrain()->setIdea(0, "I'm built different 💪😺");
		ECHO("CatA->Idea(0): " << a.getBrain()->getIdea(0));
		ECHO("CatB->Idea(0): " << b.getBrain()->getIdea(0));
    }

    ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

    return 0;
}
