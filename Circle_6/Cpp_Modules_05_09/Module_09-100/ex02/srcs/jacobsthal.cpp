/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jacobsthal.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:47:15 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/02/02 09:18:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"


/* ************************************************************************** */
/*                              Jacobsthal                                    */
/* ************************************************************************** */

static size_t jacobsthal(size_t n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	size_t a = 0;
	size_t b = 1;
	for (size_t i = 2; i <= n; ++i)
	{
		size_t tmp = b;
		b = b + a * 2;
		a = tmp;
	}
	return b;
}

std::vector<size_t> build_insertion_order(size_t k)
{
	std::vector<size_t> order;
	if (k == 0)
		return order;

	std::vector<size_t> J;
	for (size_t n = 1;; ++n)
	{
		size_t val = jacobsthal(n);
		J.push_back(val);
		if (val >= k)
			break;
	}

	size_t prev = 0;
	for (size_t i = 0; i < J.size(); ++i)
	{
		size_t curr = std::min(J[i], k);

		for (size_t idx = curr; idx > prev; --idx)
			order.push_back(idx);

		prev = curr;
		if (curr == k)
			break;
	}

	return order;
}
