/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/03 11:01:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COLOR_H
# define LIBFT_COLOR_H

/*┌────────┐
  │ color/ │
  └────────┘*/

# include <stdint.h>

/**
 * @brief Cycles through a set of predefined colors and returns the next
 *        color value.
 * @return The next color value in the loop.
 */
uint32_t	ft_loop_color_value(void);

/**
 * @brief brighten the passed color with percentage.
 * @param color The color value to apply.
 * @param percentage The percentage to brighten the color.
 */
uint32_t	ft_brighten_color(uint32_t color, int percentage);

/**
 * @brief darken the passed color with percentage.
 * @param color The color value to apply.
 * @param percentage The percentage to darken the color.
 */
uint32_t	ft_darken_color(uint32_t color, int percentage);

/**
 * @brief Changes the terminal text color to the specified color.
 * @param color The color value to apply.
 */
void		ft_change_color(uint32_t color);

/**
 * @brief Loops through a set of colors and applies them to the terminal text.
 */
void		ft_loop_color(void);

/**
 * @brief Prints a string in a rainbow gradient of colors.
 * @param str The string to print.
 */
void		ft_print_rainbow(const char *str);

/**
 * @brief Prints a string with a gradient of colors between two specified values.
 * @param str The string to print.
 * @param start The starting color value.
 * @param end The ending color value.
 */
void		ft_print_shade(const char *str, uint32_t start, uint32_t end);

/**
 * @brief Prints a string in a specified color.
 * @param str The string to print.
 * @param color The color value to apply.
 */
void		ft_print_colored(const char *str, uint32_t color);

/**
 * @brief Prints a string in a specified color, followed by a newline.
 * @param str The string to print.
 * @param color The color value to apply.
 */
void		ft_print_nl_colored(const char *str, uint32_t color);

/**
 * @brief Resets the terminal text color to the default.
 */
void		ft_reset_color(void);

#endif
