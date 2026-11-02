/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_count.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/01 11:48:14 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COUNT_H
# define LIBFT_COUNT_H

/*┌────────┐
  │ count/ │
  └────────┘*/

# include <sys/types.h>

/**
 * @brief Counts the number of words in a string separated by a given delimiter.
 * @param str The input string.
 * @param c The delimiter character.
 * @return The number of words in the string.
 */
size_t	ft_count_words(const char *str, const char c);

/**
 * @brief Calculates the length of a string.
 * @param str The input string.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str);

/**
 * @brief Calculates the length of a string up to max_len.
 * @param str The input string.
 * @param max_len The max_len to stop at if the string's len is longer.
 * @return The length of the string or max_len if longer.
 */
size_t	ft_strnlen(const char *str, size_t max_len);

/**
 * @brief Calculates the total length of a 2D array of strings.
 * @param array The input 2D array of strings.
 * @return The total number of strings in the array.
 */
size_t	ft_strlen_2d(char **array);

/**
 * @brief Calculates the length of a UTF-8 encoded string.
 * @param str The input UTF-8 string.
 * @return The number of UTF-8 characters in the string.
 */
size_t	ft_utf8_strlen(const char *str);

/**
 * @brief Calculates the length of a single UTF-8 character.
 * @param wide_c A pointer to the UTF-8 character.
 * @return The length of the UTF-8 character in bytes.
 */
size_t	ft_utf8_charlen(const char *wide_c);

/**
 * @brief Calculates the visual length of a UTF-8 encoded string.
 *
 * Example: "abc" has a visual length of 3, while "火🗿" has a visual length of 4
 *
 * @param str The input UTF-8 string.
 * @return The visual length of the string (e.g., accounting for wide
 *         characters).
 */
size_t	ft_utf8_visual_len(const char *str);

/**
 * @brief Counts the number of bytes in a UTF-8 string up to a given number of
 *        characters.
 * @param str The input UTF-8 string.
 * @param n The number of characters to count.
 * @return The number of bytes in the string up to the given character count.
 */
size_t	ft_utf8_count_bytes(const char *str, size_t n);

/**
 * @brief Counts the number of words in a string, considering quoted sections as
 *        single words.
 * @param str The input string.
 * @return The number of words in the string, treating quoted sections as
 *         single words.
 */
ssize_t	ft_count_words_quoted(const char *str);

#endif
