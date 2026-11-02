/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/15 14:23:53 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main(int argc, char** argv)
{
	{
		if (argc != 2)
		{
			ERROR("Usage: " << argv[0] << " <literal>");
			return 1;
		}

		try
		{
			ScalarConverter::convert(argv[1]);
		}
		catch (const std::exception& e)
		{
			ERROR(rgb(255, 0, 0)("Error: ") << e.what());
			return 1;
		}
	}

	return 0;
}
