/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/30 10:15:51 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#define TABLE_COLOR "\e[38;2;131;30;240m"
#define GOLD_BTC "\e[38;2;255;215;0m(₿)" TABLE_COLOR

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		ERROR(
			TABLE_COLOR BOLD
			"╭──────────────────────────────────────────╮\n"
			"│           Bitcoin Exchange " GOLD_BTC NOBOLD
											"           │\n"
			"├──────────────────────────────────────────┤\n"
			"│ Usage:                                   │\n"
			"│   ./btc <input_file>                     │\n"
			"╰──────────────────────────────────────────╯"
		);
		return 1;
	}

	TITLE("Bitcoin Exchange (₿)");
	process_file(argv[1]);
	return 0;
}
