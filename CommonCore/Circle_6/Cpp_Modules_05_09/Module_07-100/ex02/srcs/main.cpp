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

int main(void)
{
	TITLE("Int Array");
	PRINT(rgb(125,200,99));

	Array<int> intArray(5);
	for (unsigned int i = 0; i < intArray.getSize(); i++)
		intArray[i] = i * 10;

	for (unsigned int i = 0; i < intArray.getSize(); i++)
		ECHO("intArray[" << i << "] = " << intArray[i]);

	TITLE("String Array");
	PRINT(rgb(125,200,99));

	Array<std::string> strArray(3);
	strArray[0] = "Hello";
	strArray[1] = "World";
	strArray[2] = "🗿";

	for (unsigned int i = 0; i < strArray.getSize(); i++)
		ECHO("strArray[" << i << "] = " << strArray[i]);

	TITLE("Copy Constructor on intArray");
	PRINT(rgb(125,200,99));

	Array<int> copyArray(intArray);

	ECHO(B(I("Contents of copyArray:")));
	for (unsigned int i = 0; i < copyArray.getSize(); i++)
		ECHO("copyArray[" << i << "] = " << copyArray[i]);

	NEW_LINE;

	ECHO(B(I("Contents of original Array:")));
	for (unsigned int i = 0; i < intArray.getSize(); i++)
		ECHO("intArray[" << i << "] = " << intArray[i]);

	TITLE("Assignment Operator on strArray");
	PRINT(rgb(125,200,99));

	Array<std::string> assignArray;
	assignArray = strArray;

	ECHO(B(I("Contents of assignArray:")));
	for (unsigned int i = 0; i < assignArray.getSize(); i++)
		ECHO("assignArray[" << i << "] = " << assignArray[i]);

	NEW_LINE;

	ECHO(B(I("Contents of original Array:")));
	for (unsigned int i = 0; i < strArray.getSize(); i++)
		ECHO("strArray[" << i << "] = " << strArray[i]);

	TITLE("Out of bounds test");

	try
	{
		ECHO(intArray[10]);
	}
	catch (const std::out_of_range& e)
	{
		ERROR(rgb(255,123,123)(I("Caught exception: ")) << e.what());
	}

	TITLE("N size array");
	PRINT(rgb(125,200,99));

	Array<double> nArray(42);
	ECHO("Size of nArray: " << nArray.getSize());

	TITLE("Empty array");
	PRINT(rgb(125,200,99));

	Array<char> emptyArray;
	ECHO("Size of emptyArray: " << emptyArray.getSize());

	return 0;
}
