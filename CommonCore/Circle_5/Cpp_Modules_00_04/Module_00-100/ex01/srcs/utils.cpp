/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:58:21 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/30 00:02:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef EXTRA

#include "header.hpp"
#include <termios.h>
#include <unistd.h>

#if COLOR_ON
# define ITALIC "\033[3m"
#else
# define ITALIC ""
#endif

void press_enter_to_continue(void)
{
	HIDE_CURSOR;

	std::cout
		<< ITALIC << "Press "
		<< str_hex_f(ITALIC, "<", 0x929292)
		<< ITALIC << "Enter"
		<< str_hex_f(ITALIC, ">", 0x929292)
		<< ITALIC << " to continue..."
		<< std::flush;

    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c;
    do {
        read(STDIN_FILENO, &c, 1);
    } while (c != '\n');

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	SHOW_CURSOR;
}

#endif
