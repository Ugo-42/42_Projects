/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:51:56 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/14 15:16:31 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# ifdef COLOR_ON
/*┌─────────────┐
  │ Text Styles │
  └─────────────┘*/
#  define RESET_COLOR     "\033[0m"
#  define BOLD            "\033[1m"
#  define DIM             "\033[2m"
#  define ITALIC          "\033[3m"
#  define LOW_LINE        "\033[4m"
#  define BLINK           "\033[5m"
#  define REVERSE         "\033[7m"
#  define HIDDEN          "\033[8m"
#  define STRIKE          "\033[9m"
#  define DOUBLE_LOW_LINE "\033[21m"
#  define TOP_LINE        "\033[53m"
#  define TOP_LOW_LINE    "\033[4;53m"

/*┌───────────────────┐
  │ Text Basic Colors │
  └───────────────────┘*/
#  define BLACK           "\033[30m"
#  define RED             "\033[31m"
#  define GREEN           "\033[32m"
#  define YELLOW          "\033[33m"
#  define BLUE            "\033[34m"
#  define MAGENTA         "\033[35m"
#  define CYAN            "\033[36m"
#  define WHITE           "\033[37m"

/*┌────────────────────────────┐
  │ Text High Intensity Colors │
  └────────────────────────────┘*/
#  define IBLACK          "\033[90m"
#  define IRED            "\033[91m"
#  define IGREEN          "\033[92m"
#  define IYELLOW         "\033[93m"
#  define IBLUE           "\033[94m"
#  define IMAGENTA        "\033[95m"
#  define ICYAN           "\033[96m"
#  define IWHITE          "\033[97m"

/*┌───────────────────┐
  │ Background Colors │
  └───────────────────┘*/
#  define BG_BLACK        "\033[40m"
#  define BG_RED          "\033[41m"
#  define BG_GREEN        "\033[42m"
#  define BG_YELLOW       "\033[43m"
#  define BG_BLUE         "\033[44m"
#  define BG_MAGENTA      "\033[45m"
#  define BG_CYAN         "\033[46m"
#  define BG_WHITE        "\033[47m"

/*┌──────────────────────────────────┐
  │ Background High Intensity Colors │
  └──────────────────────────────────┘*/
#  define BG_IBLACK       "\033[100m"
#  define BG_IRED         "\033[101m"
#  define BG_IGREEN       "\033[102m"
#  define BG_IYELLOW      "\033[103m"
#  define BG_IBLUE        "\033[104m"
#  define BG_IMAGENTA     "\033[105m"
#  define BG_ICYAN        "\033[106m"
#  define BG_IWHITE       "\033[107m"

# else

#  define RESET_COLOR     ""
#  define BOLD            ""
#  define DIM             ""
#  define ITALIC          ""
#  define LOW_LINE        ""
#  define BLINK           ""
#  define REVERSE         ""
#  define HIDDEN          ""
#  define STRIKE          ""
#  define DOUBLE_LOW_LINE ""
#  define TOP_LINE        ""
#  define TOP_LOW_LINE    ""
#  define BLACK           ""
#  define RED             ""
#  define GREEN           ""
#  define YELLOW          ""
#  define BLUE            ""
#  define MAGENTA         ""
#  define CYAN            ""
#  define WHITE           ""
#  define IBLACK          ""
#  define IRED            ""
#  define IGREEN          ""
#  define IYELLOW         ""
#  define IBLUE           ""
#  define IMAGENTA        ""
#  define ICYAN           ""
#  define IWHITE          ""
#  define BG_BLACK        ""
#  define BG_RED          ""
#  define BG_GREEN        ""
#  define BG_YELLOW       ""
#  define BG_BLUE         ""
#  define BG_MAGENTA      ""
#  define BG_CYAN         ""
#  define BG_WHITE        ""
#  define BG_IBLACK       ""
#  define BG_IRED         ""
#  define BG_IGREEN       ""
#  define BG_IYELLOW      ""
#  define BG_IBLUE        ""
#  define BG_IMAGENTA     ""
#  define BG_ICYAN        ""
#  define BG_IWHITE       ""

# endif

#endif
