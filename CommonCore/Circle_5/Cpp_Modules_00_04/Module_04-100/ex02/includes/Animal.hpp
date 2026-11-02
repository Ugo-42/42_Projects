/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:46:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/10 11:32:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Animal
{
	protected:
		t_string _type;

	public:
		Animal();
		Animal(const Animal& other);
		virtual ~Animal();

		Animal& operator=(const Animal& other);

		virtual void makeSound() const = 0;
		t_string getType() const;
};
