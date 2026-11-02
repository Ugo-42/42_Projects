/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/21 10:57:50 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

#define TITLE(x) ECHO(BOLD << rgb(255,155,55) << "\n--- " << x << " ---" << RESET)

int main(void)
{
	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		TITLE("Setup");
		IMateriaSource* src = new MateriaSource();

		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		ICharacter* me = new Character("me");
		ICharacter* bob = new Character("bob");

		TITLE("Unknown Materia Creation");
		AMateria* tmp = src->createMateria("aice");

		TITLE("Equip NULL Materia");
		me->equip(tmp);

		TITLE("Equip Valid Materias");
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);

		TITLE("Inventory Overflow");
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		tmp = src->createMateria("ice");
		me->equip(tmp);

		TITLE("MateriaSource Overflow");
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		src->learnMateria(new Ice());

		TITLE("Using Materias");
		me->use(0, *bob);
		me->use(1, *bob);
		me->use(2, *bob);
		me->use(3, *bob);
		me->use(4, *bob);
		me->use(-1, *bob);

		TITLE("Testing deep copy");
		Character *copy = new Character(*static_cast<Character*>(me));
		copy->use(0, *bob);
		delete copy;

		TITLE("Unequip Invalid Slots");
		me->unequip(-1);
		me->unequip(4);

		TITLE("Unequip Empty Slot");
		me->unequip(0);
		me->unequip(0);

		TITLE("Use After Unequip");
		me->use(0, *bob);

		TITLE("Equip After Unequip");
		tmp = src->createMateria("ice");
		me->equip(tmp);

		TITLE("Cleanup");
		delete bob;
		delete me;
		delete src;
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
