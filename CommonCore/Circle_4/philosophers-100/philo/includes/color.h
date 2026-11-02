/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:51:56 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/22 11:30:44 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# ifdef COLOR_ON

#  define RESET_COLOR     "\033[0m"
#  define BOLD            "\033[1m"
#  define BLINK           "\033[5m"

#  define BLACK           "\033[30m"
#  define RED             "\033[31m"
#  define GREEN           "\033[32m"
#  define YELLOW          "\033[33m"
#  define BLUE            "\033[34m"
#  define MAGENTA         "\033[35m"
#  define CYAN            "\033[36m"
#  define WHITE           "\033[37m"
#  define IBLACK          "\033[90m"
#  define IRED            "\033[91m"
#  define IGREEN          "\033[92m"

#  define GRAYISH_BLUE     "\033[0;38;2;114;143;195m"
#  define LIGHT_BLUE       "\033[1;38;2;144;183;205m"
#  define WHITE_BLUE       "\033[0;38;2;194;223;255m"

# else

#  define RESET_COLOR     ""
#  define BOLD            ""
#  define BLINK           ""
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

#  define GRAYISH_BLUE     ""
#  define LIGHT_BLUE       ""
#  define WHITE_BLUE       ""

# endif

#endif
