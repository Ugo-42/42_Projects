/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  parse_location.cpp                                     ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/02/17 13:42:07 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/03/18 19:54:46 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/


#include "header.hpp"


/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                Switch key                                 │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

enum e_loc_key
{
    LOC_METHODS,
    LOC_ROOT,
    LOC_INDEX,
    LOC_AUTOINDEX,
    LOC_REDIRECT,
    LOC_UPLOAD,
	LOC_UPLOAD_DIR,
    LOC_CGI,
    LOC_UNKNOWN
};

e_loc_key getLocKey(const std::string &s)
{
	if (s == "methods"      ) return LOC_METHODS;
	if (s == "root"         ) return LOC_ROOT;
	if (s == "index"        ) return LOC_INDEX;
	if (s == "autoindex"    ) return LOC_AUTOINDEX;
	if (s == "return"       ) return LOC_REDIRECT;
	if (s == "upload_enable") return LOC_UPLOAD;
	if (s == "upload_dir"   ) return LOC_UPLOAD_DIR;
	if (s == "cgi"          ) return LOC_CGI;
	return LOC_UNKNOWN;
}

/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                Sub Parser                                 │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

t_location parseLocation(const std::vector<t_token> &tokens, size_t &i)
{
	t_location loc;

	++i;
	loc.path = parseUrlPath(tokens[i++]);

	if (tokens[i].val != "{")
		throw std::runtime_error("Expected { after location");

	++i;

	while (i < tokens.size() && tokens[i].val != "}")
	{
		switch (getLocKey(tokens[i].val))
		{
			case LOC_METHODS:
				loc.methods = parseMethods(tokens, i);
				break;

			case LOC_ROOT:
				loc.root = parseFsPath(tokens[++i]);
				break;

			case LOC_INDEX:
				loc.index = parseFilename(tokens[++i]);
				break;

			case LOC_AUTOINDEX:
				loc.autoindex = parseOnOff(tokens[++i]);
				break;

			case LOC_REDIRECT:
				loc.redirect = parseRedirection(tokens, i);
				break;

			case LOC_UPLOAD:
				loc.upload_enable = parseOnOff(tokens[++i]);
				break;

			case LOC_UPLOAD_DIR:
				loc.upload_dir = parseFsPath(tokens[++i]);
				break;

			case LOC_CGI:
				parseCgi(loc.cgi, tokens, i);
				break;

			default:
				throw parseError("Unknown location directive:", tokens[i]);
		}

		if (tokens[i + 1].val != ";")
			throw parseError("missing `;` after", tokens[i]);
		i += 2;
	}

	if (tokens[i].val != "}")
		throw std::runtime_error("Expected } after location block");

	++i;

	return loc;
}
