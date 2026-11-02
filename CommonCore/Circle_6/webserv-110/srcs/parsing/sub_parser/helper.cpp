/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  helper.cpp                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/02/17 13:42:07 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/03/19 11:34:22 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/


#include "header.hpp"


/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                 Exception                                 │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

std::invalid_argument parseError(const std::string &msg, const t_token &tok,
		const std::string &extra, TokenVisibility::Type visibility)
{
	std::string text;

	if (visibility == TokenVisibility::Show)
	{
		text = tok.val;
		if (text.length() > 20)
			text = text.substr(0, 17) + "...";
		text = " `" + text + "`";
	}

	return std::invalid_argument(
			msg + text
			+ " at line " + to_string(tok.line)
			+ ", col " + to_string(tok.col)
			+ (extra.empty() ? "" : " " + extra)
	);
}

/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                  Helpers                                  │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

size_t parseSize(const t_token &t)
{
	if (t.val.empty() || t.val == ";")
		throw parseError("empty size", t, "", TokenVisibility::Hide);

	char *endptr;
	errno = 0;
	size_t size = std::strtoul(t.val.c_str(), &endptr, 10);

	if (errno == ERANGE)
		throw parseError("size overflow", t);

	if (*(endptr + 1) != '\0')
		throw parseError("invalid size format:", t, "(supported suffixes: K, M, G)");

	switch (*endptr)
	{
		case 'K': case 'k': size *= 1024; break;
		case 'M': case 'm': size *= 1024*1024; break;
		case 'G': case 'g': size *= 1024*1024*1024; break;
		case '\0': break;
		default: throw parseError("invalid size suffix", t, "(supported suffixes: K, M, G)");
	}

	if (size > 1024*1024*1024)
		throw parseError("size too large", t, "(max: 1G)");

	return size;
}


/* ═══════════════════════════════════════════════════════════════════════════ */


int parseErrorPageValue(const t_token &t)
{
	if (t.val.empty() || t.val == ";")
		throw parseError("empty integer", t, "", TokenVisibility::Hide);

	char *endptr;
	errno = 0;
	long result = std::strtol(t.val.c_str(), &endptr, 10);

	if (errno == ERANGE || result > INT_MAX || result < INT_MIN)
		throw parseError("integer overflow", t);

	if (*endptr != '\0')
		throw parseError("invalid integer:", t);

	if (result < 100 || result > 599)
		throw parseError("invalid HTTP status code", t, "(must be between 100 and 599)");

	return static_cast<int>(result);
}


/* ═══════════════════════════════════════════════════════════════════════════ */


std::vector<std::string> parseMethods(const std::vector<t_token> &tokens, size_t &i)
{
    std::vector<std::string> methods;

    std::vector<std::string> valid_methods;
    valid_methods.push_back("GET");
    valid_methods.push_back("POST");
    valid_methods.push_back("DELETE");
	valid_methods.push_back("HEAD");

    while (++i < tokens.size() && tokens[i].val != ";")
    {
        if (std::find(valid_methods.begin(), valid_methods.end(), tokens[i].val) == valid_methods.end())
            throw parseError("Invalid method", tokens[i], "(supported: GET, POST, DELETE, HEAD)");

        methods.push_back(tokens[i].val);
    }

	--i;

    return methods;
}


/* ═══════════════════════════════════════════════════════════════════════════ */


std::pair<int, std::string> parseRedirection(const std::vector<t_token> &tokens, size_t &i)
{
	if (++i >= tokens.size())
		throw parseError("Expected status code after 'return'", tokens[i - 1]);

	char *endptr;
	errno = 0;
	long code = std::strtol(tokens[i].val.c_str(), &endptr, 10);
	if (errno == ERANGE || code <= 0 || code > 999)
		throw parseError("Redirection code out of range", tokens[i]);

	if (*endptr != '\0')
		throw parseError("Invalid format for redirection code", tokens[i]);

	if (code != 301 && code != 302 && code != 303 && code != 307)
		throw parseError("Redirection code must be [301|302|303|307]", tokens[i]);

	if (++i >= tokens.size())
		throw parseError("Expected target path after status code", tokens[i - 1]);

	std::string target = tokens[i].val;
	if (target.empty() || (target[0] != '/' && !target.find("http://") && !target.find("https://")))
		throw parseError("Redirect target must be an absolute path", tokens[i]);

	return std::make_pair(static_cast<int>(code), target);
}


/* ═══════════════════════════════════════════════════════════════════════════ */


void parseCgi(std::map<std::string, std::string> &cgi_map, const std::vector<t_token> &tokens, size_t &i)
{
	while (++i < tokens.size() && tokens[i].val != ";")
	{
		std::string ext = tokens[i].val;

		if (ext[0] != '.')
			throw parseError("CGI extension must start with '.'", tokens[i]);

		if (++i >= tokens.size() || tokens[i].val == ";")
			throw parseError("Missing interpreter for CGI extension", tokens[i - 1]);

		std::string interpreter = tokens[i].val;

		if (interpreter.empty())
			throw parseError("Invalid interpreter path for CGI", tokens[i]);

		cgi_map[ext] = interpreter;
	}

	--i;
}


/* ═══════════════════════════════════════════════════════════════════════════ */


bool parseOnOff(const t_token &t)
{
	if (t.val.empty() || t.val == ";")
		throw parseError("empty value", t, "", TokenVisibility::Hide);

	const bool on  = (t.val == "on"  || t.val == "ON"  || t.val == "On");
	const bool off = (t.val == "off" || t.val == "OFF" || t.val == "Off");

	if (!on && !off)
		throw parseError("Expected `on` or `off`, got:", t);
	return on;
}


/* ═══════════════════════════════════════════════════════════════════════════ */


std::string parseFsPath(const t_token &t)
{
	const std::string &path = t.val;

	if (path.empty() || path == ";")
		throw parseError("empty path", t, "", TokenVisibility::Hide);

	if (path[0] != '/')
		throw parseError("path must be absolute", t);

	if (path.find('\0') != std::string::npos)
		throw parseError("path contains null byte", t);

	if (path.find("..") != std::string::npos)
		throw parseError("path must not contain '..'", t);

	if (path.length() > 4096)
		throw parseError("path too long", t);

	return path;
}

/* ═══════════════════════════════════════════════════════════════════════════ */


std::string parseUrlPath(const t_token &t)
{
	const std::string &path = t.val;

	if (path.empty() || path == ";")
		throw parseError("empty location path", t, "", TokenVisibility::Hide);

	if (path[0] != '/')
		throw parseError("location path must start with '/'", t);

	if (path.find('\0') != std::string::npos)
		throw parseError("location path contains null byte", t);

	if (path.length() > 2048)
		throw parseError("location path too long", t);

	return path;
}


/* ═══════════════════════════════════════════════════════════════════════════ */


std::string parseFilename(const t_token &t)
{
	const std::string &name = t.val;

	if (name.empty() || name == ";")
		throw parseError("empty field", t, "", TokenVisibility::Hide);

	for (size_t i = 0; i < name.length(); ++i)
	{
		if (!(std::isalnum(name[i]) || name[i] == '_' || name[i] == '-' || name[i] == '.'))
			throw parseError("invalid character in ", t, "(allowed: letters, digits, '_', '-', '.')");
	}

	if (name.length() > 255)
		throw parseError("name too long", t);

	return name;
}


/* ═══════════════════════════════════════════════════════════════════════════ */


static bool isValidOctet(const std::string &s)
{
	if (s.empty() || s.size() > 3)
		return false;

	for (size_t i = 0; i < s.size(); ++i)
		if (!std::isdigit(s[i]))
			return false;

	int val = std::atoi(s.c_str());
	return val >= 0 && val <= 255;
}

static bool isValidIPv4(const std::string &ip)
{
	std::vector<std::string> octets;
	std::stringstream ss(ip);
	std::string token;

	while (std::getline(ss, token, '.'))
		octets.push_back(token);

	if (octets.size() != 4)
		return false;

	for (size_t i = 0; i < 4; ++i)
		if (!isValidOctet(octets[i]))
			return false;

	return true;
}

void parseIpPort(const t_token &t, std::string &ip, int &port)
{
	if (t.val.empty() || t.val == ";")
		throw parseError("empty listen directive", t, "", TokenVisibility::Hide);

	size_t colon_pos = t.val.find(':');
	if (colon_pos == std::string::npos)
		throw parseError("invalid listen directive format", t, "(expected format: IP:PORT)");

	std::string ip_str = t.val.substr(0, colon_pos);
	std::string port_str = t.val.substr(colon_pos + 1);

	if (ip_str.empty())
		throw parseError("empty IP in listen directive", t);
	if (port_str.empty())
		throw parseError("empty port in listen directive", t);

	if (!isValidIPv4(ip_str))
		throw parseError("invalid IPv4 address in listen directive", t);

	char *endptr;
	errno = 0;
	long port_val = std::strtol(port_str.c_str(), &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		throw parseError("port must be a numeric value", t);
	if (port_val < 1 || port_val > 65535)
		throw parseError("port out of valid range (1-65535)", t);

	ip = ip_str;
	port = static_cast<int>(port_val);
}
