/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/17 12:15:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main(void)
{
	Harl harl;

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	harl.complain("DEBUG"); ECHO("");
	harl.complain("INFO"); ECHO("");
	harl.complain("WARNING"); ECHO("");
	harl.complain("ERROR"); ECHO("");
	harl.complain("HELLO WORLD");

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
