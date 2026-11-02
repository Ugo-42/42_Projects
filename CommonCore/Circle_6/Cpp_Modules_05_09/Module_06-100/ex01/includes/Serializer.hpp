/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:04:25 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/15 15:15:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

typedef unsigned long uintptr_t;

struct Data
{
	private:
		std::string _name;

	public:
		Data(const std::string& name = "") : _name(name) {}
		std::string getName() const;
};

class Serializer
{
	private:
		Serializer() {}

	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};
