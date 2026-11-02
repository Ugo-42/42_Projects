/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_string.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 11:54:33 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRING_H
# define LIBFT_STRING_H

# include <stddef.h>

/*┌─────────┐
  │ string/ │
  └─────────┘*/

/**
 * @brief Calculates the length of the initial segment of `s` that does not
 *        contain any characters from `reject`.
 * @param s The input string.
 * @param reject The string containing characters to reject.
 * @return The length of the initial segment of `s`.
 */
size_t	ft_strcspn(const char *s, const char *reject);

/**
 * @brief Calculates the length of the initial segment of `s` that contains
 *        only characters from `accept`.
 * @param s The input string.
 * @param accept The string containing characters to accept.
 * @return The length of the initial segment of `s`.
 */
size_t	ft_strspn(const char *s, const char *accept);

/**
 * @brief Compares two strings lexicographically.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return An integer less than, equal to, or greater than zero if `s1` is
 *         found to be less than, equal to, or greater than `s2`, respectively.
 */
int		ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Compares up to `n` characters of two strings lexicographically.
 * @param s1 The first string.
 * @param s2 The second string.
 * @param n The maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if `s1` is
 *         found to be less than, equal to, or greater than `s2`, respectively.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Checks if a string has a specific file extension.
 * @param str The input string.
 * @param ext The file extension to check for.
 * @return `true` if the string ends with the specified extension,
 *         otherwise `false`.
 */
bool	ft_cmp_extension(const char *str, const char *ext);

/**
 * @brief Splits a 2D array of strings into smaller arrays based on a set of
 *        delimiters.
 * @param array The input 2D array of strings.
 * @param set The set of delimiter characters.
 * @return A pointer to the resulting 3D array of strings.
 */
char	***ft_split_2d(char **array, const char *set);

/**
 * @brief Splits a string into an array of strings using a delimiter character.
 * @param s The input string.
 * @param c The delimiter character.
 * @return A pointer to the resulting array of strings.
 */
char	**ft_split(const char *s, const char c);

/**
 * @brief Splits a string into an array of strings, treating quoted sections
 *        as single tokens.
 * @param str The input string.
 * @return A pointer to the resulting array of strings.
 */
char	**ft_split_quoted(const char *str);

/**
 * @brief Duplicates a 2D array of strings.
 * @param array The input 2D array of strings.
 * @param nmemb The number of strings to duplicate.
 * @return A pointer to the duplicated 2D array of strings.
 */
char	**ft_strdup_2d(char **array, size_t nmemb);

/**
 * @brief Joins multiple strings into a single string.
 * @param first The first string to join.
 * @param ... Additional strings to join, terminated by `NULL`.
 * @return A pointer to the resulting joined string.
 */
char	*ft_str_ultimate_join(const char *first, ...);

/**
 * @brief Searches for the first occurrence of a character in a string.
 * @param s The input string.
 * @param c The character to search for.
 * @return A pointer to the first occurrence of the character, or `NULL`
 *         if not found.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Duplicates a string.
 * @param s The input string.
 * @return A pointer to the duplicated string.
 */
char	*ft_strdup(const char *s);

/**
 * @brief Formats a string using a format specifier and additional arguments.
 *
 * Supported format specifiers:
 * - %c : character
 * - %s : string
 * - %p : pointer address
 * - %i / %d : signed int
 * - %u : unsigned int
 * - %l : signed long
 * - %x : unsigned long in lowercase hexadecimal
 * - %X : unsigned long in uppercase hexadecimal
 * - %b : convert the nb with given base (..., nb, "base", ...)
 * - %% : literal '%'
 *
 * Color format specifiers: (uint32_t color)
 * - %F : forground color
 * - %B : background color
 * - %R : reset color
 *
 * Supported alignment formats: (..., width, content, ...)
 * - %<x : left-align with padding
 * - %>x : right-align with padding
 * - %^x : center-align with padding
 *
 * @param str The format string.
 * @param args va_list with additional arguments for the format string.
 * @return A pointer to the formatted string.
 */
char	*ft_vstringf(const char *str, va_list args);

/**
 * @brief Formats a string using a format specifier and additional arguments.
 *
 * Supported format specifiers:
 * - %c : character
 * - %s : string
 * - %p : pointer address
 * - %i / %d : signed int
 * - %u : unsigned int
 * - %l : signed long
 * - %x : unsigned long in lowercase hexadecimal
 * - %X : unsigned long in uppercase hexadecimal
 * - %b : convert the nb with given base (..., nb, "base", ...)
 * - %% : literal '%'
 *
 * Color format specifiers: (uint32_t color)
 * - %F : forground color
 * - %B : background color
 * - %R : reset color
 *
 * Supported alignment formats: (..., width, content, ...)
 * - %<x : left-align with padding
 * - %>x : right-align with padding
 * - %^x : center-align with padding
 *
 * @param str The format string.
 * @param ... Additional arguments for the format string.
 * @return A pointer to the formatted string.
 */
char	*ft_stringf(const char *str, ...);

/**
 * @brief Joins two strings into a single string.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A pointer to the resulting joined string.
 */
char	*ft_strjoin(const char *s1, const char *s2);

/**
 * @brief Joins two strings into a single string and frees the input strings.
 *
 * The input strings must be dynamically allocated.
 *
 * @param s1 The first string to join.
 * @param s2 The second string to join.
 * @return A pointer to the resulting joined string.
 */
char	*ft_fstrjoin(char *s1, char *s2);

/**
 * @brief Copies a string from source to destination null-terminated.
 * @param dest The destination buffer.
 * @param src The source string.
 */
void	ft_strcpy(char *dest, const char *src);

/**
 * @brief Copies up to `n` characters from source to destination.
 * @param dest The destination buffer.
 * @param src The source string.
 * @param n The maximum number of characters to copy.
 */
void	ft_strncpy(char *dest, const char *src, size_t n);

/**
 * @brief Duplicates up to `n` characters of a string.
 * @param s The input string to duplicate.
 * @param n The maximum number of characters to duplicate.
 * @return A pointer to the newly allocated string, or NULL if allocation fails.
 */
char	*ft_strndup(const char *s, size_t n);

/**
 * @brief Locates a substring within a string, searching up to `len` characters.
 * @param big The string to search in.
 * @param little The substring to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the first occurrence of `little` in `big`, or NULL
 *         if not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Locates the last occurrence of a character in a string.
 * @param s The input string.
 * @param c The character to search for.
 * @return A pointer to the last occurrence of the character, or NULL
 *         if not found.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Copies a UTF-8 string into a destination buffer.
 * @param dest The destination buffer.
 * @param src The source UTF-8 string.
 * @param n The maximum number of UTF-8 characters to copy.
 */
void	ft_utf8_strncpy(char *dest, const char *src, size_t n);

/**
 * @brief Copies a UTF-8 string into a destination buffer, respecting
 *        visual width.
 *
 * This function ensures that the total visual width of the copied characters
 * does not exceed the specified limit. Visual width accounts for wide characters
 * such as emojis and CJK characters.
 *
 * @param dest The destination buffer.
 * @param src The source UTF-8 string.
 * @param n The maximum number of UTF-8 characters to copy.
 */
void	ft_utf8_visual_strncpy(char *dest, const char *src, size_t n);

#endif
/*** legacy ***/
/**
 * @brief Pads a string with spaces on the left to a specified width.
 * @param s The input string.
 * @param padding The total width of the padded string.
 * @return A pointer to the padded string.
 */
//char	*ft_str_left_padded(const char *s, size_t padding);

/**
 * @brief Pads a string with spaces on both sides to center it within a
 *        specified width.
 * @param s The input string.
 * @param padding The total width of the padded string.
 * @return A pointer to the padded string.
 */
//char	*ft_str_middle_padded(const char *s, size_t padding);

/**
 * @brief Pads a string with spaces on the right to a specified width.
 * @param s The input string.
 * @param padding The total width of the padded string.
 * @return A pointer to the padded string.
 */
//char	*ft_str_right_padded(const char *s, size_t padding);
