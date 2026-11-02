/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_flexistr.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/24 10:52:13 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FLEXISTR_H
# define LIBFT_FLEXISTR_H

# include <stddef.h>
# include <stdbool.h>

/**
 * @struct s_flexistr
 * @brief Represents a flexible string.
 *
 * @param string Pointer to the dynamically allocated string.
 * @param len The current length of the string (excluding the null terminator).
 * @param size The total allocated size of the string (including space for the
 *             null terminator).
 * @param last_append_len the length appended by the last executed fs_* func.
 * @param errno the exit code of last executed fs_* function.
 */
typedef struct s_flexistr
{
	char	*string;
	size_t	len;
	size_t	size;
	size_t	last_append_len;
	size_t	last_remove_len;
	int		errnum;
}	t_flexistr;

/**
 * @brief Finalizes a flexible string and returns the resulting string.
 *
 * This function detaches the string from the flexible string structure,
 * allowing the caller to manage the memory manually. The flexible string
 * structure is reset and freed even on error.
 *
 * @param fs A pointer to the flexible string structure.
 * @return A pointer to the finalized string (malloc-ated) or NULL.
 */
char	*fs_finalize(t_flexistr *fs);

/**
 * @brief Add a string at index in a flexible string.
 *
 * @param fs A pointer to the flexible string structure.
 * @param str the string to add.
 * @param index the index where we will add the string.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_add(t_flexistr *fs, const char *str, size_t index);

/**
 * @brief Removes from `start` to `end` of a flexible string.
 *
 * @param fs A pointer to the flexible string structure.
 * @param start the index where removes start
 * @param end the end index to stop removing
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_remove(t_flexistr *fs, size_t start, size_t end);

/**
 * @brief Appends a string to a flexible string unsing vstringf formats.
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
 * Supported alignment formats: (..., width, content, ...)
 * - %<x : left-align with padding
 * - %>x : right-align with padding
 * - %^x : center-align with padding
 *
 * @param fs A pointer to the flexible string structure.
 * @param s The string to append.
 * @param ... Additional arguments for the format string.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_appendf(t_flexistr *fs, const char *format, ...);

/**
 * @brief Appends a string to a flexible string.
 *
 * This function appends the given string to the flexible string. If the
 * `free_input` parameter is set to `true`, the input string is freed after
 * being appended.
 *
 * @param fs A pointer to the flexible string structure.
 * @param s The string to append.
 * @param free_input Whether to free the input string after appending.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_append(t_flexistr *fs, char *s, bool free_input);

/**
 * @brief Appends a string up to n to a flexible string.
 *
 * This function appends the given string to the flexible string up to
 * n characters.
 * 
 * @param fs A pointer to the flexible string structure.
 * @param s The string to append.
 * @param n the max number of characters to append
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_n_append(t_flexistr *fs, const char *s, size_t n);

/**
 * @brief Appends an number to a flexible string.
 *
 * This function appends the number `nb` using `base` to the flexible string
 * If base is NULL or invalid base10 will be used
 * 
 * @param fs A pointer to the flexible string structure.
 * @param nb The number to append.
 * @param base The base of the number.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_append_nb(t_flexistr *fs, long nb, const char *base);

/**
 * @brief Appends a char to a flexible string.
 *
 * This function appends the char `c` to the flexible string
 * 
 * @param fs A pointer to the flexible string structure.
 * @param c The char to append.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_append_char(t_flexistr *fs, const char c);

/**
 * @brief Initializes a flexible string with a specified initial size.
 *
 * This function allocates memory for a flexible string and sets its initial
 * size. The string is initialized as an empty string.
 *
 * @param fs A pointer to the flexible string structure.
 * @param initial_size The initial size of the flexible string.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_init(t_flexistr *fs, size_t initial_size);

/**
 * @brief Resizes a flexible string to a new size.
 *
 * This function reallocates memory for the flexible string to match the
 * specified new size. If the new size is smaller than the current length,
 * the string is truncated.
 *
 * @param fs A pointer to the flexible string structure.
 * @param new_size The new size of the flexible string.
 * @return `0` on success, `1` if bad input, or `-1` if memory allocation fails.
 */
int		fs_resize(t_flexistr *fs, size_t new_size);

/**
 * @brief Frees the memory allocated for a flexible string.
 *
 * This function frees the memory used by the flexible string and resets
 * the structure to its initial state, [NULL, 0, 0].
 *
 * @param fs A pointer to the flexible string structure.
 */
void	fs_free(t_flexistr *fs);

#endif
