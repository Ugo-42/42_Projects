/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:46:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/27 10:39:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include "config.hpp"

# define ACCESSOR(NAME, VAR) \
	t_string get##NAME() const { return VAR; } \
	void     set##NAME(const t_string &s) { VAR = s; }

class Contact
{
	private:
		t_string first_name;
		t_string last_name;
		t_string nickname;
		t_string phone_number;
		t_string darkest_secret;

	public:
		void setContact(void);

		ACCESSOR(FirstName, first_name);
		ACCESSOR(LastName, last_name);
		ACCESSOR(Nickname, nickname);
		ACCESSOR(PhoneNumber, phone_number);
		ACCESSOR(DarkestSecret, darkest_secret);
};

#endif
