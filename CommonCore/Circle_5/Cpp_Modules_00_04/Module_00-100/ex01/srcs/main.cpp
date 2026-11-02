/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/23 10:53:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#ifndef EXTRA

int main(void)
{
	PhoneBook phoneBook;
	t_string input;

	while (true)
	{
		PRINT("Enter command (ADD, SEARCH, EXIT): ");

		if (!std::getline(std::cin, input))
		{
			ECHO("\nExiting...");
			break ;
		}
		if (input == "ADD")
			phoneBook.addContact();
		else if (input == "SEARCH")
			phoneBook.searchContact();
		else if (input == "EXIT")
			break ;
		else
			PRINT("\033[A\033[K");
	}
	return (0);
}

#else

# if COLOR_ON
# define BD_COLOR "\033[0;38;2;0;130;205m"
# define TXT_COLOR "\033[0;1m"

# else

# define BD_COLOR ""
# define TXT_COLOR ""

# endif

#define HEADER BD_COLOR \
	"╭───────────────────────────────────────────────────────────╮\n" \
	"│" TXT_COLOR "   My Phone Book            Commands: (ADD, SEARCH, EXIT)  " BD_COLOR "│\n" \
	"╰───────────────────────────────────────────────────────────╯\n" RESET

int main(void)
{
	PhoneBook phoneBook;
	t_string input;

	while (true)
	{
		CLEAR_TERM;
		PRINT(HEADER);
		PRINT(BOLD + str_hex(">>> ", 0x93752A));

		if (!std::getline(std::cin, input))
		{
			ECHO("\nExiting...");
			break ;
		}
		if (input == "ADD")
			phoneBook.addContact();
		else if (input == "SEARCH")
			phoneBook.searchContact();
		else if (input == "EXIT")
			break ;
	}
	return (0);
}

#endif
