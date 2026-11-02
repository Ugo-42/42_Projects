/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:18:31 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/05 10:18:52 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

void load_data(const char *data_file, std::map<std::string, float> &data_map)
{
	std::ifstream data_stream(data_file);
	if (!data_stream.is_open())
		throw std::runtime_error("Could not open data file");

	std::string line;
	std::getline(data_stream, line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("Invalid data file header");
	while (std::getline(data_stream, line))
	{
		size_t comma_pos = line.find(',');
		if (comma_pos != std::string::npos)
		{
			std::string date = line.substr(0, comma_pos);
			float value = std::strtod(line.substr(comma_pos + 1).c_str(), NULL);
			data_map[date] = value;
		}
	}
}

bool valid_date(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

	if (month == 2)
	{
		bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (is_leap ? 29 : 28))
			return false;
	}

	return true;
}

std::string float_to_string(double f)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(5) << f;
	std::string s = oss.str();

	size_t pos = s.find('.');
	if (pos != std::string::npos)
	{
		while (!s.empty() && s[s.size() - 1] == '0')
			s.erase(s.size() - 1, 1);

		if (!s.empty() && s[s.size() - 1] == '.')
			s.erase(s.size() - 1, 1);
	}

	return s;
}
