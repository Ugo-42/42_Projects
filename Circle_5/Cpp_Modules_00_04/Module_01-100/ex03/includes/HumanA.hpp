/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:25:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/13 11:38:08 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class HumanA
{
	private:
		t_string _name;
		Weapon& _weapon;

	public:
		HumanA(const t_string& name, Weapon& weapon);
		~HumanA();

		void attack() const;
};
