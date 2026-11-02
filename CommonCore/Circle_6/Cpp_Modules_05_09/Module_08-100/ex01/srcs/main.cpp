/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/19 11:47:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <sys/random.h>

static void printList(const vec& list)
{
	PRINT((list.empty() ? BOLD "[]\n" : BOLD "["));
	for(vec::const_iterator it = list.begin(); it != list.end(); ++it)
		PRINT(*it << (it == list.end() - 1 ? "]\n" RESET : ", "));
}

static int	rand_int(void)
{
	const uint val =
		((static_cast<uint>(rand())) << 16) ^ (static_cast<uint>(rand()));
	return (static_cast<int>(val));
}

const RgbColor Blue(99, 99, 255);
const RgbColor Red(255, 99, 99);

static void runTests(int size, const vec& list,
	const std::string& testName,
	const std::string& expectedOutput1,
	const std::string& expectedOutput2)
{
	TITLE(testName);

	Span sp = Span(size);
	try
	{
		sp.addNumbers(list.begin(), list.end());
		printList(list);

		const unsigned int shortest = sp.shortestSpan();
		const unsigned int longest = sp.longestSpan();

		PRINT(I("Shortest Span: ") << shortest);
		ECHO(Blue("   // " + expectedOutput1));
		PRINT(I("Longest Span: ") << longest);
		ECHO(Blue("    // " + expectedOutput2));
	}
	catch (const std::exception &e)
	{
		ECHO(Red(B("Error: ")) << std::string(e.what()));
	}
}

#define ADD(nb) list.push_back(nb)

int main(void)
{
	{
		TITLE("Basic addNumber()");
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		ECHO(BOLD "[6, 3, 17, 9, 11]" RESET);
		PRINT(I("Shortest Span: ") << sp.shortestSpan());
		ECHO(Blue("   // 11 - 9 = 2"));
		PRINT(I("Longest Span: ") << sp.longestSpan());
		ECHO(Blue("   // 17 - 3 = 14"));
	}
	{
		vec list;
		ADD(3); ADD(9); ADD(2); ADD(4); ADD(7);
		runTests(5, list, "Span", "3 - 2 = 1", "9 - 2 = 7");
	}
	{
		vec list;
		ADD(3); ADD(4); ADD(2); ADD(4); ADD(3); ADD(2);
		runTests(6, list, "Duplicates", "4 - 4 = 0", "4 - 2 = 2");
	}
	{
		vec list;
		ADD(42); ADD(42); ADD(42); ADD(42); ADD(42); ADD(42);
		runTests(6, list, "Same number", "42 - 42 = 0", "42 - 42 = 0");
	}
	{
		vec list;
		ADD(-10); ADD(0); ADD(14); ADD(20); ADD(-21);
		runTests(5, list, "Negative numbers", "20 - 14 = 6", "20 - -21 = 41");
	}
	{
		vec list;
		ADD(1); ADD(2); ADD(3); ADD(4);
		runTests(3, list, "Span full", "N/A", "N/A");
	}
	{
		vec list;
		ADD(999);
		runTests(1, list, "Not enough numbers", "N/A", "N/A");
	}
	{
		vec emptyList;
		runTests(0, emptyList, "Empty Span", "N/A", "N/A");
	}
	{
		const int SIZE = 10000;

		TITLE("Laaarge Span");

		Span sp = Span(SIZE);
		vec largeList;

		unsigned int seed;
		getrandom(&seed, sizeof(seed), 0);
		srand(seed);

		for (int i = 0; i < SIZE; ++i)
			largeList.push_back(rand_int());
		try
		{
			sp.addNumbers(largeList.begin(), largeList.end());
			ECHO(I("Shortest Span: ") << sp.shortestSpan());
			ECHO(I("Longest Span: ") << sp.longestSpan());
		}
		catch (const std::exception &e)
		{
			ECHO(Red(B("Error: ")) << std::string(e.what()));
		}
	}
	return 0;
}
