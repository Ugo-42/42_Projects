/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 22:41:11 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/20 22:43:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "config.hpp"
#include "ICharacter.hpp"

class AMateria
{
	protected:
		t_string	_type;

	public:
		AMateria();
		AMateria(const AMateria &other);
		AMateria(const t_string &type);
		virtual ~AMateria();

		AMateria &operator=(const AMateria &other);

		const t_string		&getType() const;
		virtual AMateria	*clone() const = 0;
		virtual void		use(ICharacter &target);
};
