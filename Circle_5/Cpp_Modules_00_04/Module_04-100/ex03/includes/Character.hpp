/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:15:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/20 23:17:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"

class Character : public ICharacter
{
	private:
		t_string	_name;
		AMateria	*_inventory[4];
		AMateria	*_floor[100];
		int			_floorCount;

	public:
		Character();
		Character(const t_string &name);
		Character(const Character &other);
		virtual ~Character();

		Character &operator=(const Character &other);

		const t_string		&getName() const;
		void				equip(AMateria *m);
		void				unequip(int idx);
		void				use(int idx, ICharacter &target);

		void				clean_floor();
};
