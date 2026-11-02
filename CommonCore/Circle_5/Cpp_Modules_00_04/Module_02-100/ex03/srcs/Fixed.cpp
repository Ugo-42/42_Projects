/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:12:07 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/29 11:03:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                              Constructor                                   */
/* ************************************************************************** */


Fixed::Fixed() : _raw(0)
{
	LOG(hex(0x6ca642) + "Fixed: Default constructor called" + RESET);
}

Fixed::Fixed(const int val)
{
	LOG(hex(0xa8325c) + "Fixed: Int constructor called" + RESET);
	_raw = val << _fractionalBits;
}

Fixed::Fixed(const float val)
{
	LOG(hex(0xa8329b) + "Fixed: Float constructor called" + RESET);
	_raw = roundf(val * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed &other)
{
	LOG(hex(0x42a2a6) + "Fixed: Copy constructor called" + RESET);
	*this = other;
}


/* ************************************************************************** */
/*                               Destructor                                   */
/* ************************************************************************** */


Fixed::~Fixed()
{
	LOG(hex(0xc23030) + "Fixed: Destructor called" + RESET);
}


/* ************************************************************************** */
/*                            Assignment Operator                             */
/* ************************************************************************** */


Fixed &Fixed::operator=(const Fixed &other)
{
	LOG(hex(0x6b55d9) + "Fixed: Copy assignment operator called" + RESET);
	if (this != &other)
		_raw = other.getRawBits();
	return *this;
}


/* ************************************************************************** */
/*                                Comparisons                                 */
/* ************************************************************************** */


bool Fixed::operator>(const Fixed& other) const  { return _raw > other._raw;  }
bool Fixed::operator<(const Fixed& other) const  { return _raw < other._raw;  }
bool Fixed::operator>=(const Fixed& other) const { return _raw >= other._raw; }
bool Fixed::operator<=(const Fixed& other) const { return _raw <= other._raw; }
bool Fixed::operator==(const Fixed& other) const { return _raw == other._raw; }
bool Fixed::operator!=(const Fixed& other) const { return _raw != other._raw; }


/* ************************************************************************** */
/*                                Operations                                  */
/* ************************************************************************** */


Fixed Fixed::operator+(const Fixed& other) const
{
	Fixed res;
	res.setRawBits(_raw + other._raw);
	return res;
}

Fixed Fixed::operator-(const Fixed& other) const
{
	Fixed res;
	res.setRawBits(_raw - other._raw);
	return res;
}

Fixed Fixed::operator*(const Fixed& other) const
{
	Fixed res;
	res.setRawBits((_raw * other._raw) >> _fractionalBits);
	return res;
}

Fixed Fixed::operator/(const Fixed& other) const
{
	Fixed res;
	res.setRawBits((_raw << _fractionalBits) / other._raw);
	return res;
}


/* ************************************************************************** */
/*                          Increment / Decrement                             */
/* ************************************************************************** */


Fixed& Fixed::operator++() {
	++_raw;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed tmp(*this);
	++_raw;
	return tmp;
}

Fixed& Fixed::operator--() {
	--_raw;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed tmp(*this);
	--_raw;
	return tmp;
}


/* ************************************************************************** */
/*                               Functions                                    */
/* ************************************************************************** */


/* ---------------------------------------------------------------- */
int Fixed::getRawBits() const
{
	LOG(hex(0xd6882f) + "Fixed: getRawBits member function called" + RESET);
	return _raw;
}

void Fixed::setRawBits(int const raw)
{
	LOG(hex(0xd6672f) + "Fixed: setRawBits member function called" + RESET);
	_raw = raw;
}
/* ---------------------------------------------------------------- */



/* ------------------------------------------ */
int   Fixed::toInt(void) const {
	return _raw >> _fractionalBits;
}
float Fixed::toFloat(void) const {
	return (float)_raw / (1 << _fractionalBits);
}
/* ------------------------------------------ */



/* --------------------------------------------------- */
Fixed& Fixed::min(Fixed& a, Fixed& b) {
	return (a < b) ? a : b;
}
const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	return (a < b) ? a : b;
}
Fixed& Fixed::max(Fixed& a, Fixed& b) {
	return (a > b) ? a : b;
}
const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	return (a > b) ? a : b;
}
/* --------------------------------------------------- */


/* ************************************************************************** */
/*                              Output Operator                               */
/* ************************************************************************** */


std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return out;
}


