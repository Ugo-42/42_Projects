/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:25:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/10 11:40:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class HumanB
{
	private:
		t_string _name;
		Weapon* _weapon;

	public:
		HumanB(const t_string& name);
		~HumanB();

		void setWeapon(Weapon& weapon);
		void attack() const;
};
