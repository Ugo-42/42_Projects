/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem_manager.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/07/21 10:07:23 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEM_MANAGER_H
# define LIBFT_MEM_MANAGER_H

# include <stddef.h>

/**
 * @brief Allocates memory of the given size.
 *
 * This function allocates a block of memory, along with a metadata header,
 * and returns a pointer to the allocated memory region (excluding the header).
 *
 * @param size The size of the memory block to allocate.
 * @return A pointer to the allocated memory or NULL if allocation fails.
 */
void	*mm_alloc(size_t size);

/**
 * @brief Allocates and zeroes memory of the given size.
 *
 * This function allocates memory and sets all bytes to zero before returning
 * the pointer to the allocated memory region.
 *
 * @param size The size of the memory block to allocate.
 * @return A pointer to the allocated memory or NULL if allocation fails.
 */
void	*mm_calloc(size_t size);

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
char	*mm_stringf(const char *str, ...);

/**
 * @brief Duplicates a string a add it to the memory manager.
 * @param s The input string.
 * @return A pointer to the duplicated string.
 */
char	*mm_strdup(const char *s);

/**
 * @brief Frees the previously allocated memory.
 *
 * This function frees the memory block and its associated metadata header.
 *
 * @param ptr A pointer to the memory block to free.
 */
void	mm_free(void *ptr);

/**
 * @brief Reallocates memory to a new size.
 *
 * This function resizes a previously allocated memory block to the new size.
 * It copies the data from the old block to the new one, and frees the old block.
 *
 * @param ptr A pointer to the previously allocated memory block.
 * @param new_size The new size of the memory block.
 * @return A pointer to the newly allocated memory, or NULL if
 *         reallocation fails.
 */
void	*mm_realloc(void *ptr, size_t new_size);

/**
 * @brief Reallocates and zeroes memory to a new size.
 *
 * This function reallocates memory to the new size and sets the new memory
 * region to zero.
 *
 * @param ptr A pointer to the previously allocated memory block.
 * @param new_size The new size of the memory block.
 * @return A pointer to the newly allocated memory, or NULL if
 *         reallocation fails.
 */
void	*mm_recalloc(void *ptr, size_t new_size);

/**
 * @brief Destroys the memory manager.
 *
 * This function frees all memory allocated by the memory manager and resets
 * all internal structures to their initial state.
 */
void	mm_destroy(void);

#endif
