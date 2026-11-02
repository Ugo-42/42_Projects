/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ford_johnson.tpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:52:08 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/27 13:25:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"
#include <algorithm>
#include <vector>
#include <deque>


/* ************************************************************************** */
/*                                FORD–JOHNSON                                */
/* ************************************************************************** */

	template <typename Container>
static void merge(const Container &input, vecPair &pairs,
					typename Container::value_type &odd, bool &has_odd)
{
	has_odd = input.size() % 2 != 0;
	if (has_odd)
	{
		odd = input[input.size() - 1];
	}

	for (size_t i = 0; i < input.size() - has_odd; i += 2)
	{
		if (input[i] > input[i + 1])
			pairs.push_back(Pair(input[i], input[i + 1]));
		else
			pairs.push_back(Pair(input[i + 1], input[i]));
	}
}

	template <typename Container>
static void insertion(Container &result, const vecPair &pairs, Container &input,
						typename Container::value_type &odd, bool has_odd)
{
	typedef typename Container::iterator	Iter;

	std::vector<size_t> order = build_insertion_order(pairs.size());

	for (size_t t = 0; t < order.size(); ++t)
	{
		size_t i = order[t] - 1;
		Iter pos_winner = std::find(result.begin(), result.end(), pairs[i].big);
		Iter insert_pos = std::upper_bound(result.begin(), pos_winner, pairs[i].small);
		result.insert(insert_pos, pairs[i].small);
	}

	if (has_odd)
	{
		Iter pos = std::upper_bound(result.begin(), result.end(), odd);
		result.insert(pos, odd);
	}

	Iter out = input.begin();
	for (size_t i = 0; i < result.size(); ++i)
		*(out++) = result[i];
}

	template <typename Container>
static void ford_johnson(Container &input)
{
	if (input.size() <= 1)
		return;

	typedef typename Container::value_type	T;

	std::vector<Pair>	pairs;
	T					odd;
	bool				has_odd;

	merge(input, pairs, odd, has_odd);

	Container winners;
	for (size_t i = 0; i < pairs.size(); ++i)
		winners.push_back(pairs[i].big);

	ford_johnson(winners);

	Container result;
	if (!winners.empty())
		result = winners;

	insertion(result, pairs, input, odd, has_odd);
}

/* ************************************************************************** */
/*                                Wrappers                                    */
/* ************************************************************************** */

	template <typename T>
void ford_johnson(std::vector<T> &v)
{
	ford_johnson<std::vector<T> >(v);
}

	template <typename T>
void ford_johnson(std::deque<T> &d)
{
	ford_johnson<std::deque<T> >(d);
}

