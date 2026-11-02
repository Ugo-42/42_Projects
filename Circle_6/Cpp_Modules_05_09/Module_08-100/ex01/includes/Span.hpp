/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:40:44 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/23 10:40:48 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <stdexcept>

typedef std::vector<int> vec;

class Span
{
	private:
		unsigned int	_maxSize;
		vec				_numbers;

	public:
		Span();
		Span(unsigned int maxSize);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		unsigned int	shortestSpan() const;
		unsigned int	longestSpan() const;

		void			addNumber(int number);

		template <typename It>
		void addNumbers(It begin, It end);
};


template <typename It>
void Span::addNumbers(It begin, It end)
{
	const unsigned int rangeSize = std::distance(begin, end);
	if (_numbers.size() + rangeSize > _maxSize)
		throw std::runtime_error("Adding these numbers would exceed Span capacity");
	_numbers.insert(_numbers.end(), begin, end);
}
