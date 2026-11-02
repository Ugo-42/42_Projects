/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  parse_server.cpp                                       ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/02/17 13:42:07 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/02/17 23:41:17 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/


#include "header.hpp"


/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                Switch key                                 │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

enum e_srv_key
{
    SRV_LISTEN,
    SRV_SERVER_NAME,
    SRV_ROOT,
    SRV_CLIENT_MAX_BODY_SIZE,
    SRV_ERROR_PAGE,
    SRV_LOCATION,
    SRV_UNKNOWN
};

e_srv_key getSrvKey(const std::string &s)
{
	if (s == "listen"              ) return SRV_LISTEN;
	if (s == "server_name"         ) return SRV_SERVER_NAME;
	if (s == "root"                ) return SRV_ROOT;
	if (s == "client_max_body_size") return SRV_CLIENT_MAX_BODY_SIZE;
	if (s == "error_page"          ) return SRV_ERROR_PAGE;
	if (s == "location"            ) return SRV_LOCATION;
	return SRV_UNKNOWN;
}

/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                Sub Parser                                 │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

t_server parseServer(const std::vector<t_token> &tokens, size_t &i)
{
	t_server server;

	if (tokens[i++].val != "server")
		throw std::runtime_error("Expected server");

	if (tokens[i++].val != "{")
		throw std::runtime_error("Expected { after server");

	while (i < tokens.size() && tokens[i].val != "}")
	{
		switch (getSrvKey(tokens[i].val))
		{
			case SRV_LISTEN:
				parseIpPort(tokens[++i], server.ip, server.port);
				break;

			case SRV_SERVER_NAME:
				server.server_name = parseFilename(tokens[++i]);
				break;

			case SRV_ROOT:
				server.root = parseFsPath(tokens[++i]);
				break;

			case SRV_CLIENT_MAX_BODY_SIZE:
				server.client_max_body_size = parseSize(tokens[++i]);
				break;

			case SRV_ERROR_PAGE:
				{
					int code = parseErrorPageValue(tokens[++i]);
					std::string page = parseFsPath(tokens[++i]);
					page = FS_SRV_ROOT + page;
					server.error_pages[code] = page;
					break;
				}

			case SRV_LOCATION:
				{
					t_location loc = parseLocation(tokens, i);
					server.locations.push_back(loc);
					continue;
				}

			default:
				throw parseError("Unknown server directive:", tokens[i]);
		}

		if (tokens[i + 1].val != ";")
			throw parseError("missing `;` after", tokens[i]);
		i += 2;

	}

	if (tokens[i].val != "}")
		throw std::runtime_error("Expected } after server block");

	return server;
}
