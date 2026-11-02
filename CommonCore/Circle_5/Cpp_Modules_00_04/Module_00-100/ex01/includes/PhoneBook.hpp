/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:44:43 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/27 10:45:31 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "config.hpp"

class PhoneBook
{
	private:
		Contact contacts[8];
		unsigned int count;

	public:
		PhoneBook() : count(0) {}

		void addContact();
		void searchContact() const;
};

#endif
