/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  parser.cpp                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/02/17 11:18:49 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/03/16 23:26:26 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/


#include "header.hpp"


static std::string readFile(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not open file: " + filename);

	std::ostringstream ss;
	ss << file.rdbuf();
	return ss.str();
}


void parseConfigFile(const std::string &filename, t_config &config)
{
	const std::string content = readFile(filename);
	const std::vector<t_token> tokens = tokenize(content);
	if (tokens.empty())
		throw std::runtime_error("Empty configuration file");

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (tokens[i].val == "server")
		{
			config.servers.push_back(parseServer(tokens, i));
		}
		else
		{
			throw std::runtime_error("Unexpected token: `" + tokens[i].val
				+ "` at line " + to_string(tokens[i].line)
				+ ", col " + to_string(tokens[i].col));
		}
	}
}
