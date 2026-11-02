/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:02:13 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/27 00:05:55 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

void Contact::setContact(void)
{
	t_string input;

	const t_string prompts[] = {
		" — First Name: ",
		" — Last Name: ",
		" — Nickname: ",
		" — Phone Number: ",
		" — Darkest Secret: "
	};

	void (Contact::*setters[])(const t_string&) = {
		&Contact::setFirstName,
		&Contact::setLastName,
		&Contact::setNickname,
		&Contact::setPhoneNumber,
		&Contact::setDarkestSecret
	};

	for (size_t i = 0; i < 5; ++i)
	{
		while (true)
		{
			PRINT(prompts[i]);
			if (!std::getline(std::cin, input))
			{
				ECHO("\nExiting...");
				std::exit(0);
			}
			if (!input.empty())
			{
				(this->*setters[i])(input);
				break;
			}
			PRINT("\033[A\033[K");
		}
	}
	#ifdef EXTRA
	press_enter_to_continue();
	#endif
}
