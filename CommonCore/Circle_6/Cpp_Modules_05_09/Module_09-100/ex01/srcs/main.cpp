/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/07 13:40:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

int main(int argc, char **argv)
{
	RgbColor Red(255, 99, 99);

	if (argc < 2)
	{
		ERROR(Red("Error: ") + "no RPN expression provided.");
		return 1;
	}

	std::stack<int> s;
	std::string expr = argv[1];

	for (size_t i = 0; i < expr.length(); ++i)
	{
		char c = expr[i];

		if (c == ' ')
			continue;

		if (c >= '0' && c <= '9')
			s.push(c - '0');
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (s.size() < 2)
			{
				ERROR(Red("Error: ") + "insufficient values in expression");
				return 1;
			}
			int b = s.top();
			s.pop();
			int a = s.top();
			s.pop();

			int result;
			if (c == '+')
				result = a + b;
			else if (c == '-')
				result = a - b;
			else if (c == '*')
				result = a * b;
			else
			{
				if (b == 0)
				{
					ERROR(Red("Error: ") + "division by zero");
					return 1;
				}
				result = a / b;
			}
			s.push(result);
		}
		else
		{
			ERROR(Red("Error: ") + "invalid character encountered");
			return 1;
		}
	}

	if (s.size() != 1)
	{
		ERROR(Red("Error: ") + "insufficient operators in expression");
		return 1;
	}

	ECHO(s.top());
	return 0;
}
