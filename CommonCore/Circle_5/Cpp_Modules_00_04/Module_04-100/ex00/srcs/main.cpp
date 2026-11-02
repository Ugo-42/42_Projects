/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/11/10 11:32:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

int main( void )
{
	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		const Animal* meta = new Animal();
		const Animal* dog = new Dog();
		const Animal* cat = new Cat();
		const WrongAnimal* wrongmeta = new WrongAnimal();
		const WrongAnimal* wrongcat = new WrongCat();

		std::cout << meta->getType() << " " << std::endl;
		std::cout << dog->getType() << " " << std::endl;
		std::cout << cat->getType() << " " << std::endl;
		std::cout << wrongmeta->getType() << " " << std::endl;
		std::cout << wrongcat->getType() << " " << std::endl;
		dog->makeSound();
		cat->makeSound();
		meta->makeSound();
		wrongmeta->makeSound();
		wrongcat->makeSound();

		delete meta;
		delete dog;
		delete cat;
		delete wrongmeta;
		delete wrongcat;
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	{
		WrongCat wrongCat;
		wrongCat.makeSound();
	}

	ECHO(rgb(150,0,0) + "——————————————————————————————————————" + RESET);

	return 0;
}
