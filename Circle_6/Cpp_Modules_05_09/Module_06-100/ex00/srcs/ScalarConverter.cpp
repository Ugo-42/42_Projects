/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:25:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/12 15:26:11 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "config.hpp"
#include <cerrno>
#include <cfloat>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

/* ************************************************************************** */
/*                               Print Helpers                                */
/* ************************************************************************** */


void printColored(const std::string &title, const std::string &value)
{
	ECHO(rgb(62, 186, 0)(title) << rgb(186, 155, 0)(value));
}

void printChar(double d)
{
	if (std::isnan(d) || d < 0 || d > 127 || d != static_cast<int>(d))
		printColored("char: ", "impossible");
	else if (!std::isprint(static_cast<unsigned char>(d)))
		printColored("char: ", "Non displayable");
	else
		printColored("char: ", "'" + std::string(1, static_cast<char>(d)) + "'");
}

void printInt(double d)
{
	if (std::isnan(d) || d < INT_MIN || d > INT_MAX)
		printColored("int: ", "impossible");
	else
	{
		std::ostringstream oss;
		oss << static_cast<int>(d);
		printColored("int: ", oss.str());
	}
}

void printFloat(double d)
{
	if (std::isnan(d))
		printColored("float: ", "nanf");
	else
	{
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(1) << static_cast<float>(d);
		printColored("float: ", oss.str() + "f");
	}
}

void printDouble(double d)
{
	if (std::isnan(d))
		printColored("double: ", "nan");
	else
	{
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(1) << d;
		printColored("double: ", oss.str());
	}
}


/* ************************************************************************** */
/*                                 Converter                                  */
/* ************************************************************************** */


bool isCharLiteral(const std::string s)
{
	return s.size() == 1 && std::isprint(s[0]) && !std::isdigit(s[0]);
}

bool parseNumber(const std::string& s, double& out)
{
	char* end = NULL;
	errno = 0;

	out = strtod(s.c_str(), &end);

	return errno == 0 && (*end == '\0' || (*end == 'f' && *(end + 1) == '\0'));
}

void ScalarConverter::convert(const std::string& literal)
{
	if (isCharLiteral(literal))
	{
		const char c = literal[0];

		std::ostringstream i, f, d;
		i << static_cast<int>(c);
		f << std::fixed << std::setprecision(1) << static_cast<float>(c);
		d << std::fixed << std::setprecision(1) << static_cast<double>(c);

		printColored("char: ", "'" + std::string(1, c) + "'");
		printColored("int: ", i.str());
		printColored("float: ", f.str() + "f");
		printColored("double: ", d.str());
		return;
	}

    double value;
    if (!parseNumber(literal, value))
    {
		throw std::invalid_argument("Invalid literal: `" + literal + '`');
    }

    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}

