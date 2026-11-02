/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:01:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/22 11:03:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* ************************************************************************** */
/*                                <SETTINGS>                                  */
/* ************************************************************************** */

#define SET_COLOR_ON    1
#define LOG_ON          1
#define EXTRA           0

/* ************************************************************************** */
/*                                 <CONFIG>                                   */
/* ************************************************************************** */

/* =============================== INCLUDES ================================= */

#include <iostream>
#include <sstream>
#include <string>

/* ================================ MACROS ================================== */

#define PRINT(...) do { std::cout << __VA_ARGS__; } while(0)
#define ECHO(...) do { std::cout << __VA_ARGS__ << '\n'; } while(0)
#define ERROR(...) do { std::cerr << __VA_ARGS__ << '\n'; } while(0)

#define CLEAR_TERM  std::cout << "\033[2J\033[1;1H" << std::flush
#define HIDE_CURSOR std::cout << "\033[?25l" << std::flush
#define SHOW_CURSOR std::cout << "\033[?25h" << std::flush
#define NEW_LINE    std::cout << std::endl
#define UP          std::cout << "\033[A" << std::flush
#define DOWN        std::cout << "\033[B" << std::flush
#define LEFT        std::cout << "\033[D" << std::flush
#define RIGHT       std::cout << "\033[C" << std::flush

#if LOG_ON
# define LOG(...) do { std::cout << __VA_ARGS__ << '\n'; } while(0)
#else
# define LOG(msg) do { } while(0)
#endif /* end LOG_ON */

#define noexcept throw()

/* ================================ TYPEDEF ================================= */

typedef std::string t_string;
typedef unsigned long uintptr_t;

/* =============================== TEMPLATES ================================ */

template <typename T>
static inline t_string to_string(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

/* ************************************************************************** */
/*                                   COLOR                                    */
/* ************************************************************************** */

#if SET_COLOR_ON

#include <sstream>

/* =============================== RAW CODES ================================ */

#define RESET    "\033[0m"
#define BOLD     "\033[1m"
#define ITALIC   "\033[3m"
#define BLINK    "\033[6m"
#define NOBOLD   "\033[22m"
#define NOITALIC "\033[23m"
#define NOBLINK  "\033[26m"

/* ============================== TEXT EFFECTS ============================== */

static inline t_string B(const t_string& text)
{
	return BOLD + text + NOBOLD;
}

static inline t_string B(const char* text)
{
	return BOLD + t_string(text) + NOBOLD;
}

static inline t_string I(const t_string& text)
{
	return ITALIC + text + NOITALIC;
}

static inline t_string I(const char* text)
{
	return ITALIC + t_string(text) + NOITALIC;
}

/* =============================== RGB GUARD ================================ */
/* Usage: rgb(x,y,z)("text") → auto color reset */

struct RgbColor
{
	t_string prefix;

	RgbColor(int r, int g, int b)
	{
		std::ostringstream s;
		s << "\033[38;2;" << r << ";" << g << ";" << b << "m";
		prefix = s.str();
	}

	t_string operator()(const t_string& text) const
	{
		return prefix + text + RESET;
	}

	t_string operator()(const char* text) const
	{
		return prefix + t_string(text) + RESET;
	}

	operator const char*() const
	{
		return prefix.c_str();
	}
};

static inline RgbColor rgb(int r, int g, int b)
{
	return RgbColor(r, g, b);
}

/* ================================ TITLE ==================================== */

static inline void TITLE(const t_string& text)
{
	static bool init = false;

	if (!init)
		init = true;
	else
		std::cout << '\n';

	ECHO(BOLD << rgb(255,155,55)("--- " + text + " ---"));
}

/* =========================== COLOR DISABLED MODE =========================== */

#else

#define RESET  ""
#define BOLD   ""
#define ITALIC ""
#define BLINK  ""
#define NOBOLD   ""
#define NOITALIC ""
#define NOBLINK  ""

static inline t_string B(const t_string& text) { return text; }
static inline t_string B(const char* text) { return t_string(text); }
static inline t_string I(const t_string& text) { return text; }
static inline t_string I(const char* text) { return t_string(text); }

struct RgbColor
{
	RgbColor(int, int, int) {}
	t_string operator()(const t_string& text) const { return text; }
	t_string operator()(const char* text) const { return t_string(text); }
};

static inline RgbColor rgb(int, int, int)
{
	return RgbColor(0,0,0);
}

static inline void TITLE(const t_string& text)
{
	static bool init = false;

	if (!init)
		init = true;
	else
		std::cout << '\n';

	ECHO("--- " << text << " ---");
}

#endif /* SET_COLOR_ON */

