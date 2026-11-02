/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:32:26 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/18 15:32:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
class Array
{
	private:
		T				*_array;
		unsigned int	_size;

	public:
		Array();
		Array(unsigned int n);
		Array(const Array &other);
		~Array();

		Array &operator=(const Array &other);
		T &operator[](unsigned int index);
		const T &operator[](unsigned int index) const;

		unsigned int getSize() const;
};


#include <stdexcept>
#include <utility>


/* ************************************************************************** */
/*                                Constructors                                */
/* ************************************************************************** */


template <typename T>
Array<T>::Array() : _array(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(const Array &other) : _array(new T[other._size]()), _size(other._size)
{
	for (unsigned int i = 0; i < _size; i++)
		_array[i] = other._array[i];
}


/* ************************************************************************** */
/*                                 Destructor                                 */
/* ************************************************************************** */


template <typename T>
Array<T>::~Array()
{
	delete[] _array;
}


/* ************************************************************************** */
/*                                 Operators                                  */
/* ************************************************************************** */


template <typename T>
Array<T> &Array<T>::operator=(const Array &other)
{
	if (this != &other)
	{
		delete[] _array;
		_size = other._size;
		_array = new T[_size]();
		for (unsigned int i = 0; i < _size; i++)
			_array[i] = other._array[i];
	}
	return *this;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _array[index];
}

template <typename T>
const T &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _array[index];
}


/* ************************************************************************** */
/*                               Member Functions                             */
/* ************************************************************************** */


template <typename T>
unsigned int Array<T>::getSize() const
{
	return _size;
}

