/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:58:39 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/29 11:34:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

/* ************************************************************************** */
/*                               Constructor                                  */
/* ************************************************************************** */


Point::Point() : _x(0), _y(0)
{
	LOG(hex(0x6ca642) + "Point: Default constructor called" + RESET);
}

Point::Point(const float x, const float y) : _x(x), _y(y)
{
	LOG(hex(0xa8329b) + "Point: Float constructor called" + RESET);
}

Point::Point(const Point& other) : _x(other._x), _y(other._y)
{
	LOG(hex(0x42a2a6) + "Point: Copy constructor called" + RESET);
}

Point& Point::operator=(const Point& other)
{
	LOG(hex(0x6b55d9) + "Point: Copy assignment operator called" + RESET);
	if (this != &other)
	{
		LOG(hex(0xff0000) + "Warning: cannot assign to const members" + RESET);
	}
	return *this;
}


/* ************************************************************************** */
/*                               Destructor                                   */
/* ************************************************************************** */


Point::~Point()
{
	LOG(hex(0xc23030) + "Point: Destructor called" + RESET);
}


/* ************************************************************************** */
/*                               Functions                                    */
/* ************************************************************************** */


Fixed Point::getX() const { return _x; }
Fixed Point::getY() const { return _y; }


