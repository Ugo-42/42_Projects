/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/13 10:30:38 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main(int argc, char **argv)
{
	bool quiet = false;
	if (argc == 5 && t_string(argv[1]) == "-q")
	{
		quiet = true;
		++argv;
		--argc;
	}

	if (argc != 4)
	{
		ERROR(
			"Usage: " << argv[0] << " filename s1 s2\n"
			" - Options: -q (quiet)"
		);
		return 1;
	}


	FileReplacer fr(argv[1], argv[2], argv[3]);
	fr.readAndReplace();
	if (!quiet)
		fr.printChanges();

	return 0;
}
