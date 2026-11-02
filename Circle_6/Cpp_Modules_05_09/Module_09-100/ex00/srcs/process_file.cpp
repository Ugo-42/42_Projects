/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:29:56 by ugwentzi          #+#    #+#             */
/*   Updated: 2026/01/21 13:03:06 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include <cstdlib>
#include <fstream>
#include <map>

void process_file(const char *filename)
{
	RgbColor Red(255, 0, 0);
	RgbColor Blue(140, 140, 255);
	RgbColor Gold(255, 215, 0);

	std::ifstream file(filename);
	if (!file.is_open())
	{
		ERROR(Red("Error: ") << "Could not open file: " << I(filename));
		return;
	}

	std::map<std::string, float> data_map;
	try
	{
		load_data("data.csv", data_map);
	}
	catch (const std::exception &e)
	{
		ERROR(Red("Error: ") << "Failed to load data from data.csv");
		return;
	}

	std::string line;
	std::getline(file, line);
	if (line != "date | value")
	{
		ERROR(Red("Error: ") << "Invalid file header in: " << I(filename));
		return;
	}

	while (std::getline(file, line))
	{
		size_t pipe_pos = line.find('|');
		if (pipe_pos == std::string::npos)
		{
			ERROR(Red("Error: ") << '`' << B(I(line)) << '`' << " invalid line format.");
			continue;
		}

		if ((pipe_pos > 1 && line[pipe_pos - 1] != ' ') || (pipe_pos + 1 < line.length() && line[pipe_pos + 1] != ' '))
		{
			ERROR(Red("Error: ") << '`' << B(I(line)) << '`' << " invalid line format.");
			continue;
		}

		std::string date = line.substr(0, pipe_pos - 1);
		float value = std::strtod(line.substr(pipe_pos + 2).c_str(), NULL);

		std::map<std::string, float>::iterator it = data_map.lower_bound(date);
		if (it == data_map.end() || it->first != date)
		{
			if (!valid_date(date))
			{
				ERROR(Red("Error: ") << '`' << B(I(date)) << "` invalid date.");
				continue;
			}
			if (it == data_map.begin())
			{
				ERROR(Red("Error: ") << '`' << B(I(date)) << "` no data found.");
				continue;
			}
			--it;
		}

		float exchange_rate = it->second;
		float result = value * exchange_rate;

		if (value < 0)
		{
			ERROR(Red("Error: ") << "`" << B(I(float_to_string(value))) << "` not a positive number.");
			continue;
		}
		if (value > 1000.0)
		{
			ERROR(Red("Error: ") << "`" << B(I(float_to_string(value))) << "` too large number.");
			continue;
		}
		ECHO(Blue << date << " => " << Gold << float_to_string(value) << "₿ "
				<< Blue << "= " << Gold << float_to_string(result) << "$"
				<< rgb(99,99,111) << " (" << it->first << ")" << RESET);
	}
}
