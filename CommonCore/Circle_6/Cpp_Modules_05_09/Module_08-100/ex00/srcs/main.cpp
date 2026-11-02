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
#include <list>

template <typename Container>
void testEasyFind(Container& c, int value)
{
	try
	{
		typename Container::iterator it = easyfind(c, value);
		ECHO("Found value: " << *it);
	}
	catch (const std::exception& e)
	{
		ECHO(rgb(255,123,123)(I("Exception: ")) << e.what());
	}
}


int main(void)
{
	{
		TITLE("find in list");

		std::list<int> lst;
		for (int i = 1; i <= 10; ++i)
			lst.push_back(i * 5);

		testEasyFind(lst, 25);

		TITLE("find non-existing value");
		testEasyFind(lst, 42);
	}

	{
		TITLE("find in vector");

		std::vector<int> v;
		for (int i = 1; i <= 10; ++i)
			v.push_back(i * 10);

		testEasyFind(v, 70);

		TITLE("find non-existing value");
		testEasyFind(v, 15);
	}

	return 0;
}
