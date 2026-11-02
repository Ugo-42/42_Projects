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

int main(void)
{
	int dummy;
	srand(static_cast<unsigned int>(time(NULL) ^ reinterpret_cast<uintptr_t>(&dummy)));

	TITLE("Iter with int");

	int array[] = {1, 2, 3, 4, 5};
	const size_t length = sizeof(array) / sizeof(array[0]);

	::iter(array, length, &print);

	TITLE("Iter with char");

	char c_array[] = {'a', 'b', 'c', 'd', 'e'};
	const size_t c_length = sizeof(c_array) / sizeof(c_array[0]);

	::iter(c_array, c_length, &print);

	TITLE("Iter with const string");

	const t_string s_array[] = {"hello", "world", "this", "is", "C++", "ᕙ🗿ᕗ"};
	const size_t s_length = sizeof(s_array) / sizeof(s_array[0]);

	::iter(s_array, s_length, &print);

	return 0;
}
