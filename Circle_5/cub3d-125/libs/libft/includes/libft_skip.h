/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_skip.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/20 09:42:00 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_SKIP_H
# define LIBFT_SKIP_H

/*┌───────┐
  │ skip/ │
  └───────┘*/

/**
 * @brief Skips over a quoted section in a string.
 *
 * This function advances the string pointer to skip over a quoted section,
 * including the opening and closing quotes.
 *
 * @param str A pointer to the address of the string pointer to modify.
 * @return The number of characters skipped, including the quotes.
 */
int		ft_skip_quoted(const char **str);

/**
 * @brief Skips over consecutive occurrences of a specific character.
 * @param str A pointer to the address of the string pointer to modify.
 * @param c The character to skip.
 */
void	ft_skip_chars(const char **str, const char c);

/**
 * @brief Skips over consecutive characters that are part of a given set.
 * @param str A pointer to the address of the string pointer to modify.
 * @param set A null-terminated string representing the set of characters
 *            to skip.
 */
void	ft_skip_chars_in_set(const char **str, const char *set);

/**
 * @brief Skips over consecutive characters that are not a specific character.
 * @param str A pointer to the address of the string pointer to modify.
 * @param c The character to stop skipping at.
 */
void	ft_skip_not_chars(const char **str, const char c);

/**
 * @brief Skips over whitespace characters in a string.
 * @param str A pointer to the address of the string pointer to modify.
 */
void	ft_skip_spaces(const char **str);

/**
 * @brief Skips over a single word in a string.
 *
 * A word is defined as a sequence of non-whitespace characters.
 *
 * @param str A pointer to the address of the string pointer to modify.
 */
void	ft_skip_word(const char **str);

#endif
