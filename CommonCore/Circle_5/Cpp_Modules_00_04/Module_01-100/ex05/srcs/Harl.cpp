/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:29:44 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/17 12:13:21 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <iostream>

void Harl::debug(void)
{
	ECHO(
		hex(0x96cc2b) + "[DEBUG]\n" +
		ITALIC +
		"I love having extra bacon for my 7XL-double-cheese-"
		"triple-pickle-special-ketchup burger.\n"
		"I really do!" +
		RESET
	);
}

void Harl::info(void)
{
	ECHO(
		hex(0xffd500) + "[INFO]\n" +
		ITALIC +
		"I cannot believe adding extra bacon costs more money.\n"
		"You didn’t put enough bacon in my burger!\n"
		"If you did, I wouldn’t be asking for more!" +
		RESET
	);
}

void Harl::warning(void)
{
	ECHO(
		hex(0xff6f00) + "[WARNING]\n" +
		ITALIC +
		"I think I deserve to have some extra bacon for free.\n"
		"I’ve been coming for years, whereas "
		"you started working here just last month." +
		RESET
	);
}

void Harl::error(void)
{
	ECHO(
		hex(0xff0000) + "[ERROR]\n" +
		RESET + BOLD + hex(0xff0000) + ITALIC +
		"This is unacceptable!\n"
		"I want to speak to the manager now." +
		RESET
	);
}

void Harl::complain(t_string level)
{
	void (Harl::*functions[4])(void) = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	t_string levels[4] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};

	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			(this->*functions[i])();
			return;
		}
	}

	ECHO(hex(0xCC44ff) + "Harl doesn't know this level." + RESET);
}
