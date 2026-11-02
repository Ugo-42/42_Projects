/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:20:15 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/30 09:54:12 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_COLOR_H
# define CUB3D_COLOR_H

# ifdef COLOR_ON

#  define RESET            "\033[0m"
#  define BOLD             "\033[1m"

#  define RED              "\033[38;2;255;0;0m"
#  define GRAYISH_BLUE     "\033[0;38;2;114;143;195m"
#  define LIGHT_BLUE       "\033[1;38;2;144;183;205m"
#  define WHITE_BLUE       "\033[0;38;2;194;223;255m"
#  define DARKER_RED       "\033[38;2;25;0;0m"
#  define BLACK            "\033[38;2;0;0;0m"
#  define WHITE            "\033[38;2;255;255;255m"
#  define GREEN            "\033[38;2;0;255;0m"
#  define MOSS_GREEN       "\033[38;2;72;146;4m"
#  define ORANGE           "\033[38;2;255;100;46m"
#  define YELLOW           "\033[38;2;255;222;0m"
#  define CYAN             "\033[38;2;0;255;222m"
#  define TURQUOISE        "\033[38;2;8;155;148m"
#  define BG_DARK_RED      "\033[48;2;75;0;0m"
#  define BG_DARKER_RED    "\033[48;2;45;0;0m"
#  define LIGHT_RED        "\033[38;2;255;96;96m"
#  define LIGHT_BROWN      "\033[38;2;111;22;22m"
#  define BG_DARK_PURPLE   "\033[48;2;60;20;90m"
#  define BG_DARKER_PURPLE "\033[48;2;30;10;45m"
#  define LIGHT_PURPLE     "\033[38;2;220;130;180m"
#  define PURPLE           "\033[38;2;100;50;120m"
#  define BLUE             "\033[38;2;42;77;155m"
#  define TURQUOISE_GREEN  "\033[38;2;0;168;122m"
#  define EMERAULD         "\033[38;2;42;144;111m"
#  define SAPHIRE          "\033[38;2;15;82;186m"
#  define ORANGE2          "\033[38;2;255;127;80m"

# else

#  define RESET            ""
#  define BOLD             ""

#  define RED              ""
#  define GRAYISH_BLUE     ""
#  define LIGHT_BLUE       ""
#  define WHITE_BLUE       ""
#  define DARKER_RED       ""
#  define BLACK            ""
#  define WHITE            ""
#  define GREEN            ""
#  define MOSS_GREEN       ""
#  define ORANGE           ""
#  define YELLOW           ""
#  define CYAN             ""
#  define TURQUOISE        ""
#  define BG_DARK_RED      ""
#  define BG_DARKER_RED    ""
#  define LIGHT_RED        ""
#  define LIGHT_BROWN      ""
#  define BG_DARK_PURPLE   ""
#  define BG_DARKER_PURPLE ""
#  define LIGHT_PURPLE     ""
#  define PURPLE           ""
#  define BLUE             ""
#  define TURQUOISE_GREEN  ""
#  define EMERAULD         ""
#  define SAPHIRE          ""
#  define ORANGE2          ""

# endif

#endif
