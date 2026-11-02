/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_conversion.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/21 13:39:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERSION_H
# define LIBFT_CONVERSION_H

# include <stdbool.h>
# include <stdint.h>

/*┌─────────────┐
  │ conversion/ │
  └─────────────┘*/

/**
 * @brief Converts a string to an integer.
 * @param str The string to convert.
 * @return The integer value of the string.
 */
int		ft_atoi(const char *str);

/**
 * @brief Converts an uppercase character to lowercase.
 * @param c The character to convert.
 * @return The lowercase equivalent of the character, or the original character
 *         if it is not uppercase.
 */
int		ft_tolower(int c);

/**
 * @brief Converts a lowercase character to uppercase.
 * @param c The character to convert.
 * @return The uppercase equivalent of the character, or the original character
 *         if it is not lowercase.
 */
int		ft_toupper(int c);

/**
 * @brief Converts an integer to a string.
 * @param n The integer to convert.
 * @return A string representation of the integer.
 */
char	*ft_itoa(int n);

#endif
/*** legacy ***/
/**
 * @brief Converts a memory address to a string representation.
 * @param addr The memory address to convert.
 * @param uppercase Whether to use uppercase letters for hexadecimal digits.
 * @return A string representation of the memory address.
 */
//char	*ft_addrtoa(uintptr_t addr, bool uppercase);

/**
 * @brief Converts a character to a string.
 * @param c The character to convert.
 * @return A string containing the character.
 */
//char	*ft_ctoa(char c);

/**
 * @brief Converts an unsigned integer to a string.
 * @param n The unsigned integer to convert.
 * @return A string representation of the unsigned integer.
 */
//char	*ft_utoa(unsigned int n);

/**
 * @brief Converts an unsigned long integer to a hexadecimal string.
 * @param n The unsigned long integer to convert.
 * @param uppercase Whether to use uppercase letters for hexadecimal digits.
 * @return A string representation of the hexadecimal value.
 */
//char	*ft_xtoa(unsigned long n, bool uppercase);
