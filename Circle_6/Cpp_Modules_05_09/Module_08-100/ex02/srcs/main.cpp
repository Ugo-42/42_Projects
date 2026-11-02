/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/16 14:32:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <vector>

int main(void)
{
	{
		TITLE("stack capabilities");

		MutantStack<int> mstack;

		mstack.push(5);

		ECHO(I("Top element: ") << mstack.top());
		ECHO(I("Size: ") << mstack.size());

		mstack.push(17);

		NEW_LINE;
		ECHO(I("Top element: ") << mstack.top());
		ECHO(I("Size: ") << mstack.size());

		mstack.pop();

		NEW_LINE;
		ECHO(I("Size after pop: ") << mstack.size());
		ECHO(I("Top element after pop: ") << mstack.top());

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);

		TITLE("MutantStack iteration");

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		while (it != ite)
		{
			PRINT(*it << (it != ite - 1 ? ", " : "\n"));
			++it;
		}

		TITLE("Reverse iteration");

		MutantStack<int>::reverse_iterator rit = mstack.rbegin();
		MutantStack<int>::reverse_iterator rite = mstack.rend();

		while (rit != rite)
		{
			PRINT(*rit << (rit != rite - 1 ? ", " : "\n"));
			++rit;
		}
	}

	{
		TITLE("other container test");

		MutantStack<int, std::vector<int> > mstack;

		for (int i = 0; i < 10; ++i)
			mstack.push(i);

		MutantStack<int, std::vector<int> >::iterator it = mstack.begin();
		MutantStack<int, std::vector<int> >::iterator ite = mstack.end();

		while (it != ite)
		{
			PRINT(*it << (it != ite - 1 ? ", " : "\n"));
			++it;
		}

		NEW_LINE;

		MutantStack<int, std::vector<int> >::reverse_iterator rit = mstack.rbegin();
		MutantStack<int, std::vector<int> >::reverse_iterator rite = mstack.rend();

		while (rit != rite)
		{
			PRINT(*rit << (rit != rite - 1 ? ", " : "\n"));
			++rit;
		}
	}

	return 0;
}
