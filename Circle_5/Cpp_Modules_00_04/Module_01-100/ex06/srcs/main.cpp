/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/17 11:58:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int get_lvl(const t_string &level)
{
    if ( level == "DEBUG"   ) return 0;
    if ( level == "INFO"    ) return 1;
    if ( level == "WARNING" ) return 2;
    if ( level == "ERROR"   ) return 3;

    return -1;
}

int main(int argc, char **argv)
{
	if (argc < 2) return 0;

	Harl harl;

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	switch (get_lvl(argv[1]))
	{
		case 0:
			harl.complain("DEBUG");
			ECHO("");
		case 1:
			harl.complain("INFO");
			ECHO("");
		case 2:
			harl.complain("WARNING");
			ECHO("");
		case 3:
			harl.complain("ERROR");
			break;
		default:
			harl.complain("HELLO WORLD");
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
