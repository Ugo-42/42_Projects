/*┌───────────────────────────────────────────────────────────────────────────┐*/
/*│                                                                           │*/
/*│  client.hpp                                             ▒▒▒▒    ▒▒▒▒      │*/
/*│                                                         ▒▒▒▒    ▒▒▒▒      │*/
/*│  By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒          │*/
/*│                                                           ▒▒▒▒▒▒▒▒        │*/
/*│  Created: 2026/03/31 22:52:04 by ugwentzi                 ▒▒▒▒▒▒▒▒        │*/
/*│  Updated: 2026/04/05 01:35:43 by ugwentzi                 ▒▒    ▒▒        │*/
/*│                                                                           │*/
/*└───────────────────────────────────────────────────────────────────────────┘*/

#pragma once

struct Cgi
{
	time_t	start_time;

	int		stdout_fd;
	int		stdin_fd;
	pid_t	pid;

	std::string buffer;

    bool    pipe_closed;
    bool    process_done;
};

struct Client
{
	int fd;

	std::string read_buffer;
	std::string write_buffer;

	size_t	body_size;
	size_t	max_body_size;
	size_t	content_length;

	enum State {
		READING,
		PROCESSING,
		WRITING,
		CGI_RUNNING,
	} state;

	Cgi cgi;

	bool	should_close;
	bool	headers_parsed;
};

