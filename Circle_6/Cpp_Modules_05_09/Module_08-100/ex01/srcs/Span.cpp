/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:59:27 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/23 10:59:42 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <algorithm>
#include <stdexcept>
#include <climits>


/* ************************************************************************** */
/*                               Constructors                                 */
/* ************************************************************************** */


Span::Span()
	: _maxSize(0) {}

Span::Span(unsigned int maxSize)
	: _maxSize(maxSize) {}

Span::Span(const Span &other)
	: _maxSize(other._maxSize)
	, _numbers(other._numbers) {}


/* ************************************************************************** */
/*                                Destructor                                  */
/* ************************************************************************** */


Span::~Span() {}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}


/* ************************************************************************** */
/*                                 Methods                                    */
/* ************************************************************************** */


void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw std::runtime_error("Span is already full");
	_numbers.push_back(number);
}


unsigned int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers to find a span");

	vec sortedNumbers = _numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());

	unsigned int span, minSpan = UINT_MAX;
	for (size_t i = 1; i < sortedNumbers.size(); ++i)
	{
		span = static_cast<unsigned int>(sortedNumbers[i] - sortedNumbers[i - 1]);
		if (span < minSpan)
			minSpan = span;
	}
	return minSpan;
}

unsigned int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers to find a span");

	const int min = *std::min_element(_numbers.begin(), _numbers.end());
	const int max = *std::max_element(_numbers.begin(), _numbers.end());

	return static_cast<unsigned int>(max - min);
}

