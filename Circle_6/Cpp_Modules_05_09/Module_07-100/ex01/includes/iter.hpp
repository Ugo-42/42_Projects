/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:39:55 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/18 14:40:02 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include "config.hpp"

template <typename T>
void iter(T *array, const size_t length, void (*func)(T &))
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}

template <typename T>
void iter(const T *array, const size_t length, void (*func)(const T &))
{
	for (size_t i = 0; i < length; i++)
		func(array[i]);
}


template <typename T>
void print(const T &x)
{
	RgbColor color = RgbColor(rand() % 256, rand() % 256, rand() % 256);

	ECHO(B(color(to_string(x))));
}
