/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/09 13:17:28 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main( void )
{
	t_string str = "HI THIS IS BRAIN";
	t_string* stringPTR = &str;
	t_string& stringREF = str;

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	ECHO("str       : " << &str);
	ECHO("stringPTR : " << stringPTR);
	ECHO("stringREF : " << &stringREF);

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	ECHO("str       : " << str);
	ECHO("stringPTR : " << *stringPTR);
	ECHO("stringREF : " << stringREF);

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

    return 0;
}

