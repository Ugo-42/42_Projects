/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:35:49 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/20 23:37:52 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria *_templates[4];

	public:
		MateriaSource();
		MateriaSource(const MateriaSource &other);
		virtual ~MateriaSource();

		MateriaSource &operator=(const MateriaSource &other);

		void		learnMateria(AMateria *m);
		AMateria	*createMateria(const t_string &type);
};
