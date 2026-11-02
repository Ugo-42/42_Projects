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
#include <iomanip>

template <typename T>
void printColored(const RgbColor color, const std::string& title, const T& content)
{
	ECHO(color(title + ": " + std::string(28 - title.length(), ' ') + "[ ")
			<< std::setw(15) << std::left << content << color(" ]"));
}

int main(void)
{
	Data data("MySecretData");

	printColored(rgb(0,186,255), "Original Data name", data.getName());
	printColored(rgb(99,255,68), "Original Data address", &data);

	uintptr_t raw = Serializer::serialize(&data);

	std::ostringstream ss;
	ss << "0x" << std::hex << raw;
	printColored(rgb(186,0,255), "Serialized Data (uintptr_t)", ss.str());

	Data* deserializedData = Serializer::deserialize(raw);

	printColored(rgb(255,0,186), "Deserialized Data address", deserializedData);
	printColored(rgb(0,255,186), "Deserialized Data name", deserializedData->getName());

	return 0;
}
