/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:22:41 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/16 14:32:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <cstdlib>
#include <ctime>

/* ************************************************************************** */
/*                               Constants                                    */
/* ************************************************************************** */

const RgbColor colorA = rgb(0, 255, 0);
const RgbColor colorB = rgb(66, 255, 191);
const RgbColor colorC = rgb(191, 255, 66);

/* ************************************************************************** */
/*                               Functions                                    */
/* ************************************************************************** */

Base *generate(void)
{
	static int	init;
	if (!init)
	{
		int dummy;
		srand(static_cast<unsigned int>(time(NULL)
				+ reinterpret_cast<uintptr_t>(&dummy)));
		init = 1;
	}

	switch (rand() % 3)
	{
		case 0:
			ECHO(colorA("Generated instance of type A"));
			return new A();
		case 1:
			ECHO(colorB("Generated instance of type B"));
			return new B();
		case 2:
			ECHO(colorC("Generated instance of type C"));
			return new C();
	}
	return NULL;
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		ECHO(colorA("Identified type: A"));
	else if (dynamic_cast<B*>(p))
		ECHO(colorB("Identified type: B"));
	else if (dynamic_cast<C*>(p))
		ECHO(colorC("Identified type: C"));
	else
		ECHO(rgb(255,255,100)("Identified type: Unknown"));
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		ECHO(colorA("Identified type: A"));
		return;
	}
	catch (...) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		ECHO(colorB("Identified type: B"));
		return;
	}
	catch (...) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		ECHO(colorC("Identified type: C"));
		return;
	}
	catch (...) {}

	ECHO(rgb(255,255,100)("Identified type: Unknown"));
}

/* ************************************************************************** */
/*                                 Main                                       */
/* ************************************************************************** */


int main(void)
{
	const int	testCount = 10;
	Base*		instances[testCount];

	TITLE("Generating instances");
	for (int i = 0; i < testCount; ++i)
		instances[i] = generate();

	TITLE("Identifying instances by pointer");
	for (int i = 0; i < testCount; ++i)
		identify(instances[i]);

	TITLE("Identifying instances by reference");
	for (int i = 0; i < testCount; ++i)
		identify(*instances[i]);

	TITLE("Cleaning up");
	for (int i = 0; i < testCount; ++i)
	{
		ECHO(rgb(200,100,200)("Deleting instance at address: ") << instances[i]);
		delete instances[i];
	}

	return 0;
}
