/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:34:17 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/20 23:36:20 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual	~IMateriaSource() {}

		virtual void		learnMateria(AMateria *m) = 0;
		virtual AMateria	*createMateria(const t_string &type) = 0;
};
