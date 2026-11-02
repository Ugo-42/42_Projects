/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_allocation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/04/04 10:10:31 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ALLOCATION_H
# define LIBFT_ALLOCATION_H

# include <stdlib.h>

/*┌─────────────┐
  │ allocation/ │
  └─────────────┘*/

/**
 * @brief Allocates memory for an array of elements and initializes it to zero.
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Allocates memory for a 2D array and initializes it to zero.
 * @param dim1 First dimension size.
 * @param dim2 Second dimension size.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated 2D array, or NULL if allocation fails.
 */
void	*ft_calloc_2d(size_t dim1, size_t dim2, size_t size);

/**
 * @brief Frees a 2D array of characters and sets the pointers to NULL.
 * @param array A pointer to the 2D array to free.
 * @return NULL for convenience, allowing chaining with assignments.
 */
void	*ft_free_2d_char_array(char ***array);

/**
 * @brief Frees a file descriptor and sets it to -1.
 * @param fd Address to the file descriptor to free.
 * @return -1 on error or the return value of close.
 */
int		ft_close_null(int *fd);

/**
 * @brief Frees a pointer and sets it to NULL.
 * @param pointer_address Address of the pointer to free.
 * @return NULL for convenience, allowing chaining with assignments.
 */
void	*ft_free_null(void *pointer_address);

/**
 * @brief Frees a 2D array and sets it to NULL.
 * @param array_address Address of the 2D array to free.
 * @param n Number of rows to free.
 * @return NULL for convenience, allowing chaining with assignments.
 */
void	*ft_free_null_2d(void *array_address, size_t n);

/**
 * @brief Allocates memory for a 2D array without initialization.
 * @param dim1 First dimension size.
 * @param dim2 Second dimension size.
 * @param size Size of each element in bytes.
 * @return A pointer to the allocated 2D array, or NULL if allocation fails.
 */
void	*ft_malloc_2d(size_t dim1, size_t dim2, size_t size);

/**
 * @brief Reallocates memory for a block of memory and set the rest to '\0'.
 * @param ptr Pointer to the previously allocated memory.
 * @param old_size Size of the previously allocated memory.
 * @param new_size Size of the new memory block.
 * @return A pointer to the reallocated memory, or NULL if reallocation fails.
 */
void	*ft_recalloc(void *ptr, size_t old_size, size_t new_size);

/**
 * @brief Reallocates memory for a block of memory.
 * @param ptr Pointer to the previously allocated memory.
 * @param old_size Size of the previously allocated memory.
 * @param new_size Size of the new memory block.
 * @return A pointer to the reallocated memory, or NULL if reallocation fails.
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
