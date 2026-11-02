/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  header.hpp                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/02/17 13:08:22 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/03/18 19:42:24 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

#include "config.hpp"

/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                 Structs                                   │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

struct t_location
{
	bool								autoindex;
	bool								upload_enable;
	std::string							index;
	std::string							path;
	std::string							root;
	std::string							upload_dir;
	std::vector<std::string>			methods;
	std::pair<int, std::string>			redirect;
	std::map<std::string, std::string>	cgi;

	t_location() : autoindex(false), upload_enable(false) {}
};

struct t_server
{
	size_t						client_max_body_size;
	std::map<int, std::string>	error_pages;
	std::string					ip;
	int							port;
	std::string					root;
	std::string					server_name;
	std::vector<t_location>		locations;

	t_server() : client_max_body_size(0), root("/") {}
};

struct t_config
{
	std::vector<t_server> servers;
};

struct t_token
{
	std::string		val;
	size_t			line;
	size_t			col;

	t_token(const std::string &v, size_t l, size_t c)
		: val(v)
		, line(l)
		, col(c) {}
};

/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                Functions                                  │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/


/* ════════════════════════════════ PARSER ═══════════════════════════════════ */

namespace TokenVisibility
{
    enum Type
    {
        Show,
        Hide
    };
}

std::invalid_argument parseError(
    const std::string &msg, const t_token &tok, const std::string &extra = "",
    TokenVisibility::Type visibility = TokenVisibility::Show
);

bool								parseOnOff(const t_token &t);
size_t								parseSize(const t_token &t);
int									parseErrorPageValue(const t_token &t);
void								parseIpPort(const t_token &t, std::string &ip, int &port);
std::string							parseFsPath(const t_token &t);
std::string							parseUrlPath(const t_token &t);
std::string							parseFilename(const t_token &t);
std::vector<std::string>			parseMethods(const std::vector<t_token> &tokens, size_t &i);
std::pair<int, std::string>			parseRedirection(const std::vector<t_token> &tokens, size_t &i);
void								parseCgi(std::map<std::string, std::string> &cgi_map, const std::vector<t_token> &tokens, size_t &i);

std::vector<t_token>				tokenize(const std::string &content);

void								parseConfigFile(const std::string &filename, t_config &config);
t_location							parseLocation(const std::vector<t_token> &tokens, size_t &i);
t_server							parseServer(const std::vector<t_token> &tokens, size_t &i);
