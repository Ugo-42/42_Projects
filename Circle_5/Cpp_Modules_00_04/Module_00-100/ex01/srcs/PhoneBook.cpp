/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:14:24 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/02 09:33:59 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

void PhoneBook::addContact(void)
{
	static int index;

	contacts[index++ % 8].setContact();
	if (count < 8)
	{
		count++;
	}
}

#ifndef EXTRA

static t_string format_field(const t_string &str)
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return t_string(10 - str.length(), ' ') + str;
}

void PhoneBook::searchContact() const
{
	if (count > 0)
		std::cout << BOLD << "| Index | First Name | Last Name  |  Nickname  |" << RESET << std::endl;
	else
	{
		ECHO("No contact found.");
		return ;
	}

	for (unsigned int i = 0; i < count; ++i)
	{
		std::cout << "|   " << i + 1 << "   | "
		          << format_field(contacts[i].getFirstName()) << " | "
		          << format_field(contacts[i].getLastName()) << " | "
		          << format_field(contacts[i].getNickname()) << " |" << std::endl;
	}

	PRINT("Enter index to display: ");

	t_string input;
	if (!std::getline(std::cin, input))
		return ;

	if (input.length() != 1 || !isdigit(input[0]))
	{
		PRINT("Invalid index.\n");
		return ;
	}

	int idx = input[0] - '0' - 1;
	if (idx < 0 || idx >= static_cast<int>(count))
	{
		PRINT("No contact at that index.\n");
		return ;
	}

	std::cout << BOLD << "First Name: " << RESET << contacts[idx].getFirstName() << std::endl;
	std::cout << BOLD << "Last Name: " << RESET << contacts[idx].getLastName() << std::endl;
	std::cout << BOLD << "Nickname: " << RESET << contacts[idx].getNickname() << std::endl;
	std::cout << BOLD << "Phone Number: " << RESET << contacts[idx].getPhoneNumber() << std::endl;
	std::cout << BOLD << "Darkest Secret: " << RESET << contacts[idx].getDarkestSecret() << std::endl;
}

#else

static t_string format_field(const t_string &str)
{
	if (str.length() > 10)
		return str.substr(0, 9) + "…";
	return t_string(10 - str.length(), ' ') + str;
}

void PhoneBook::searchContact() const
{
	if (count > 0)
	{
		ECHO(hex(0x93752A) + "╭───────┬────────────┬────────────┬────────────╮");
		std::cout << BOLD << "│ Index │ First Name │ Last Name  │  Nickname  │" << RESET << std::endl;

	}
	else
	{
		ECHO("\n No contact found.\n");
		press_enter_to_continue();
		return ;
	}

	for (unsigned int i = 0; i < count; ++i)
	{
		std::cout << str_hex("│   ", 0x93752A) << i + 1 << str_hex("   │ ", 0x93752A)
		          << format_field(contacts[i].getFirstName()) << str_hex(" │ ", 0x93752A)
		          << format_field(contacts[i].getLastName()) << str_hex(" │ ", 0x93752A)
		          << format_field(contacts[i].getNickname()) << str_hex(" │", 0x93752A) << std::endl;
	}
	ECHO(str_hex("╰───────┴────────────┴────────────┴────────────╯", 0x93752A));

	t_string input;
	while (true)
	{
		PRINT("Enter index to display: ");
		if (!std::getline(std::cin, input))
			return ;
		if (!input.empty())
			break ;
		PRINT("\033[A\033[K");
	}

	if (input.length() != 1 || !isdigit(input[0]))
	{
		PRINT("\033[A\033[K");
		ECHO("Invalid index.\n");
		press_enter_to_continue();
		return ;
	}

	int idx = input[0] - '0' - 1;
	if (idx < 0 || idx >= static_cast<int>(count))
	{
		PRINT("\033[A\033[K");
		ECHO("No contact at that index.\n");
		press_enter_to_continue();
		return ;
	}

	PRINT("\033[A\033[K\033[B");
	std::cout << BOLD << " — First Name: " << RESET << contacts[idx].getFirstName() << std::endl;
	std::cout << BOLD << " — Last Name: " << RESET << contacts[idx].getLastName() << std::endl;
	std::cout << BOLD << " — Nickname: " << RESET << contacts[idx].getNickname() << std::endl;
	std::cout << BOLD << " — Phone Number: " << RESET << contacts[idx].getPhoneNumber() << std::endl;
	std::cout << BOLD << " — Darkest Secret: " << RESET << contacts[idx].getDarkestSecret() << std::endl;
	ECHO("");

	press_enter_to_continue();
}

#endif
