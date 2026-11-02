/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:01:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/27 09:26:47 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ************************************************************************** */
/*                            ---=| SETTINGS |=---                            */
/* ************************************************************************** */

# define SET_RANDOM_SEED 1
# define SET_COLOR_ON    1

/* ************************************************************************** */
/*                             ---=| CONFIG |=---                             */
/* ************************************************************************** */


/*=--   -+-   -+-   -+-   -+-   --=[ Macros ]=--   -+-   -+-   -+-   -+-   --=*/

# define ECHO(msg) std::cout << (msg) << std::endl;
# define PRINT(msg) std::cout << (msg);

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

#  define RESET "\033[0m"
#  define BOLD  "\033[1m"

inline const t_string rgb(int r, int g, int b)
{
	std::ostringstream s;
	s << "\033[38;2;" << r << ";" << g << ";" << b << "m";
	return (s.str());
}

inline const t_string hex(int hex) {
	return (rgb((hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF));
}

inline const t_string random_color() {
    return rgb(std::rand() % 256, std::rand() % 256, std::rand() % 256);
}

# else

#  define RESET          ""
#  define BOLD           ""
inline t_string rgb(int, int, int) { return ""; }
inline t_string hex(int) { return ""; }
inline t_string random_color() { return ""; }

# endif /* end COLOR_ON */


#endif
