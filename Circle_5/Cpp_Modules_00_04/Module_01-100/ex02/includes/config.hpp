/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:01:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/09 13:21:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ************************************************************************** */
/*                            ---=| SETTINGS |=---                            */
/* ************************************************************************** */

# define SET_RANDOM_SEED 0
# define SET_COLOR_ON    1

/* ************************************************************************** */
/*                             ---=| CONFIG |=---                             */
/* ************************************************************************** */

/*=--   -+-   -+-   -+-   -+-  --=[ Includes ]=--  -+-   -+-   -+-   -+-   --=*/

# include <iostream>

/*=--   -+-   -+-   -+-   -+-   --=[ Macros ]=--   -+-   -+-   -+-   -+-   --=*/

# define ECHO(...) do { std::cout << __VA_ARGS__ << std::endl; } while(0)

# define PRINT(...) do { std::cout << __VA_ARGS__; } while(0)


# define CLEAR_TERM std::cout << "\033[2J\033[1;1H" << std::flush
# define HIDE_CURSOR std::cout << "\033[?25l" << std::flush
# define SHOW_CURSOR std::cout << "\033[?25h" << std::flush

/*=--   -+-   -+-   -+-   -+-   --=[ Typedef ]=--  -+-   -+-   -+-   -+-   --=*/

typedef std::string t_string;
typedef std::string::size_type t_string_size;

/* ************************************************************************** */
/*                                   Random                                   */
/* ************************************************************************** */

# if SET_RANDOM_SEED

# include <sys/time.h>
# include <cstdlib>
# include <climits>
# include <iostream>

__attribute__((constructor))
static void set_random_seed(void)
{
	static const unsigned long	MASK  = 0xA5A5A5A5A5A5A5A5ULL;
	static const unsigned long	CONST = 0x9E3779B97F4A7C15ULL;
	static const unsigned long	MULT1 = 0xBF58476D1CE4E5B9ULL;
	static const unsigned long	MULT2 = 0x94D049BB133111EBULL;
	unsigned long		seed;
	struct timeval		tv;

	gettimeofday(&tv, NULL);

	seed = static_cast<unsigned long>(tv.tv_sec)
		^ static_cast<unsigned long>(tv.tv_usec) ^ MASK;

	seed += CONST;
	seed ^= (seed >> 30); seed *= MULT1;
	seed ^= (seed >> 27); seed *= MULT2;
	seed ^= (seed >> 31);

	srand(static_cast<unsigned int>(seed & ULONG_MAX));
}

# endif /* end SET_RANDOM_SEED */

/* ************************************************************************** */
/*                                   Color                                    */
/* ************************************************************************** */

# if SET_COLOR_ON

#  ifndef COLOR_ON
#   define COLOR_ON
#  endif

# else

#  ifdef COLOR_ON
#   undef COLOR_ON
#  endif

# endif /* end SET_COLOR_ON */


# ifdef COLOR_ON
# include <sstream>
# include <cstdlib>

#  define RESET "\033[0m"
#  define BOLD  "\033[1m"

inline const t_string rgb(int r, int g, int b)
{
	std::ostringstream s;
	s << "\033[38;2;" << r << ";" << g << ";" << b << "m";
	return (s.str());
}

inline const t_string hex(int color) {
	return (rgb((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF));
}

inline const t_string random_color() {
    return (rgb(std::rand() % 256, std::rand() % 256, std::rand() % 256));
}

inline const t_string str_hex(const t_string& text, int color) {
	return (hex(color) + text + RESET);
}

inline const t_string str_hex_f(const t_string &format, const t_string &text, int color) {
	return (format + hex(color) + text + RESET);
}

# else

#  define RESET          ""
#  define BOLD           ""
inline t_string rgb(int, int, int) { return ""; }
inline t_string hex(int) { return ""; }
inline t_string random_color() { return ""; }
inline t_string str_hex(const t_string& txt, int) { return txt; }
inline t_string str_hex_f(const t_string &, const t_string &txt, int) { return txt; }

# endif /* end COLOR_ON */


#endif
