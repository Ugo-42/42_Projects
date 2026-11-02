/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_memory.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/21 13:52:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEMORY_H
# define LIBFT_MEMORY_H

# include <stddef.h>

/*┌─────────┐
  │ memory/ │
  └─────────┘*/

/**
 * @brief Compares two memory blocks.
 * @param s1 Pointer to the first memory block.
 * @param s2 Pointer to the second memory block.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if the first
 *         n bytes of `s1` are found to be less than, equal to, or greater
 *         than `s2`, respectively.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Searches for a byte in a memory block.
 * @param s Pointer to the memory block.
 * @param c The byte to search for.
 * @param n Number of bytes to search.
 * @return A pointer to the first occurrence of the byte, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Copies memory from one location to another.
 * @param dest Pointer to the destination memory block.
 * @param src Pointer to the source memory block.
 * @param n Number of bytes to copy.
 * @return A pointer to the destination memory block.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Moves memory from one location to another, handling overlap.
 * @param dest Pointer to the destination memory block.
 * @param src Pointer to the source memory block.
 * @param n Number of bytes to move.
 * @return A pointer to the destination memory block.
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Sets a memory block to a specified value.
 * @param s Pointer to the memory block.
 * @param c The value to set.
 * @param n Number of bytes to set.
 * @return A pointer to the memory block.
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Sets a memory block to zero.
 * @param s Pointer to the memory block.
 * @param n Number of bytes to set to zero.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Sets multiple memory blocks to zero based on a format string.
 *
 *   >_ you need to separate each type with a comma ','.
 *
 *   Exemple: ["i,c,zu,d", (int)&a, (char)&b, (size_t)&c, (double)&d]
 *
 *   >_ you can put nb before the type to repeat same type.
 *
 *   Exemple: ["3i,2p", (int)&a, (int)&b, (int)&c, (void *)&d, (void *)&e]
 *
 * @param format A format string specifying the memory blocks to zero.
 * @param ... Additional arguments specifying the memory blocks.
 */
void	ft_ultimate_bzero(const char *format, ...);

/**
 * @brief Swaps the addresses of two pointers.
 * @param a_address Pointer to the first memory address.
 * @param b_address Pointer to the second memory address.
 */
void	ft_swap_address(void *a_address, void *b_address);

/**
 * @brief Swaps the contents of two memory blocks.
 * @param a Pointer to the first memory block.
 * @param b Pointer to the second memory block.
 * @param type_size The size of each memory block in bytes.
 */
void	ft_swap_content(void *a, void *b, size_t type_size);

#endif
