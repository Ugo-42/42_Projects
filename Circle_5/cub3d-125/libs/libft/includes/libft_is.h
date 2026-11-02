/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_is.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/24 21:44:23 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IS_H
# define LIBFT_IS_H

/*┌───────┐
  │  is/  │
  └───────┘*/

/**
 * @brief Checks if a character is a CJK (Chinese, Japanese, Korean) character.
 * @param wide_c A pointer to a wide character string.
 * @return `true` if the character is CJK, otherwise `false`.
 */
bool	ft_is_cjk(const char *wide_c);

/**
 * @brief Checks if a character is an emoji.
 * @param wide_c A pointer to a wide character string.
 * @return `true` if the character is an emoji, otherwise `false`.
 */
bool	ft_is_emoji(const char *wide_c);

/**
 * @brief Checks if a character is in a given set of characters.
 * @param c The character to check.
 * @param set A null-terminated string representing the set of characters.
 * @return `true` if the character is in the set, otherwise `false`.
 */
bool	ft_is_in_set(const char c, const char *set);

/**
 * @brief Checks if a character is not in a given set of characters.
 * @param c The character to check.
 * @param set A null-terminated string representing the set of characters.
 * @return `true` if the character is not in the set, otherwise `false`.
 */
bool	ft_is_not_in_set(const char c, const char *set);

/**
 * @brief Checks if a number is a power of 2.
 * @param n The number to check.
 * @return `true` if the number is a power of 2, otherwise `false`.
 */
bool	ft_is_power_of_2(uint32_t n);

/**
 * @brief Checks if a character is alphanumeric.
 * @param c The character to check.
 * @return Non-zero if the character is alphanumeric, otherwise 0.
 */
int		ft_is_alnum(int c);

/**
 * @brief Checks if a character is alphabetic.
 * @param c The character to check.
 * @return Non-zero if the character is alphabetic, otherwise 0.
 */
int		ft_is_alpha(int c);

/**
 * @brief Checks if a character is an ASCII character.
 * @param c The character to check.
 * @return Non-zero if the character is an ASCII character, otherwise 0.
 */
int		ft_is_ascii(int c);

/**
 * @brief Checks if a character is a digit.
 * @param c The character to check.
 * @return Non-zero if the character is a digit, otherwise 0.
 */
int		ft_is_digit(int c);

/**
 * @brief Checks if a character is printable.
 * @param c The character to check.
 * @return Non-zero if the character is printable, otherwise 0.
 */
int		ft_is_print(int c);

/**
 * @brief Checks if a character is a quote character (' or ").
 * @param c The character to check.
 * @return Non-zero if the character is a quote, otherwise 0.
 */
int		ft_is_quote(int c);

/**
 * @brief Checks if a character is a whitespace character.
 * @param c The character to check.
 * @return Non-zero if the character is a whitespace character, otherwise 0.
 */
int		ft_is_space(int c);

#endif
