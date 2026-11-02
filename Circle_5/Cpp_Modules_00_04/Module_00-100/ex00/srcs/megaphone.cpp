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

t_string	shout(const t_string &str)
{
	t_string	result = str;

	for (t_string_size i = 0; i < result.length(); ++i)
		result[i] = std::toupper(result[i]);
	return (result);

}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ECHO(BOLD + random_color() + DEFAULT_MSG RESET);
		return (0);
	}
	PRINT(BOLD + random_color());
	for (int i = 1; i < argc; ++i)
		PRINT(shout(argv[i]));
	ECHO(RESET);
	return (0);
}
