/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:12:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/24 13:53:36 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                              Constructors                                  */
/* ************************************************************************** */


Fixed::Fixed() : _raw(0)
{
	ECHO(hex(0x6ca642) + "Default constructor called" + RESET);
}

Fixed::Fixed(const int val)
{
	ECHO(hex(0xa8325c) + "Int constructor called" + RESET);
	_raw = val << _fractionalBits;
}

Fixed::Fixed(const float val)
{
	ECHO(hex(0xa8329b) + "Float constructor called" + RESET);
	_raw = roundf(val * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed &other)
{
	ECHO(hex(0x42a2a6) + "Copy constructor called" + RESET);
	*this = other;
}


/* ************************************************************************** */
/*                               Destructors                                  */
/* ************************************************************************** */


Fixed::~Fixed()
{
	ECHO(hex(0xc23030) + "Destructor called" + RESET);
}


/* ************************************************************************** */
/*                                Operators                                   */
/* ************************************************************************** */


Fixed &Fixed::operator=(const Fixed &other)
{
	ECHO(hex(0x6b55d9) + "Copy assignment operator called" + RESET);
	if (this != &other)
		_raw = other.getRawBits();
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return out;
}


/* ************************************************************************** */
/*                               Functions                                    */
/* ************************************************************************** */


int Fixed::getRawBits() const
{
	ECHO(hex(0xd6882f) + "getRawBits member function called" + RESET);
	return _raw;
}

void Fixed::setRawBits(int const raw)
{
	ECHO(hex(0xd6672f) + "setRawBits member function called" + RESET);
	_raw = raw;
}

int Fixed::toInt(void) const
{
	return _raw >> _fractionalBits;
}

float Fixed::toFloat(void) const
{
	return (float)_raw / (1 << _fractionalBits);
}

