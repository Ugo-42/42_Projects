/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  tokenizer.cpp                                          ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/02/17 11:33:24 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/03/01 21:35:22 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/


#include "header.hpp"


static void pushToken(std::vector<t_token> &tokens, std::string &tok, size_t line, size_t col)
{
	if (!tok.empty())
	{
		tokens.push_back(t_token(tok, line, col));
		tok.clear();
	}
}

static void InsertBlankIfEmpty(std::vector<t_token> &tokens, size_t line)
{
	if (tokens.empty())
		return;

	const t_token &last = tokens.back();

	const char *directives[] = {
		"listen", "server_name", "root", "location", "error_page",
		"methods", "index", "cgi", "upload_dir", "redirect",
		"upload_enable", "autoindex"
	};

	bool isDirective = false;
	for (size_t i = 0; i < sizeof(directives)/sizeof(directives[0]); ++i)
		if (last.val == directives[i])
			isDirective = true;

	if (isDirective)
		tokens.push_back(t_token("", line, 1));
}

std::vector<t_token> tokenize(const std::string &content)
{
	std::vector<t_token> tokens;
	std::string current;
	size_t line = 1;
	size_t col = 1;
	size_t start_col = 1;

	for (size_t i = 0; i < content.size(); ++i)
	{
		char c = content[i];

		if (c == '\n')
		{
			pushToken(tokens, current, line, start_col);

			InsertBlankIfEmpty(tokens, line);

			++line;
			col = 1;
			continue;
		}

		if (c == '#')
		{
			pushToken(tokens, current, line, start_col);
			while (i < content.size() && content[i] != '\n')
				++i;
			++line;
			col = 1;
			continue;
		}

		if (std::isspace(c))
		{
			pushToken(tokens, current, line, start_col);
		}

		else if (c == '{' || c == '}' || c == ';')
		{
			pushToken(tokens, current, line, start_col);
			tokens.push_back(t_token(std::string(1, c), line, col));
		}

		else
		{
			if (current.empty())
				start_col = col;
			current += c;
		}

		++col;

	}

	pushToken(tokens, current, line, start_col);

	return tokens;
}
