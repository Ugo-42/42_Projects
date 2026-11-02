/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:25:59 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/10 11:39:09 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class Weapon
{
	private:
		t_string _type;

	public:
		Weapon(const t_string& type);
		~Weapon();

		const t_string& getType() const;
		void setType(const t_string& type);
};
