/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_flexistr_2d.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieffel <lrieffel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:02:17 by lrieffel          #+#    #+#             */
/*   Updated: 2025/04/30 10:29:45 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FLEXISTR_2D_H
# define LIBFT_FLEXISTR_2D_H

# include "libft.h"

typedef struct s_flexistr2d
{
	char	**str;
	size_t	len;
	size_t	alloc_size;
}	t_flexistr2d;

/**
 * @brief Initializes a 2D flexible string array structure.
 *
 * This function sets up a flexible 2D string array structure with the given
 * base pointer and initial size. It prepares the structure for further
 * operations such as adding or modifying strings. The fuction also
 * frees the `base` pointer.
 *
 * @param arstr Pointer to the t_flexistr2d structure to initialize.
 * @param base Pointer to the base array of strings.
 * @param initial_size The initial size of the 2D string array.
 * @return Returns 0 on success, or a non-zero value on failure.
 */
int		flexistr2d_finit(t_flexistr2d *arstr,
			char **base, size_t initial_size);

/**
 * @brief Initializes a 2D flexible string array.
 * 
 * This function sets up a flexible 2D string array structure with an initial
 * size and a base pointer to manage the array's memory and contents.
 * 
 * @param arstr Pointer to the t_flexistr2d structure to initialize.
 * @param base Pointer to the base array of strings.
 * @param initial_size The initial size of the 2D string array.
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int		flexistr2d_init(t_flexistr2d *arstr, char **base, size_t initial_size);

/**
 * @brief Appends a string to a flexible 2D string array.
 * 
 * This function adds the provided string to the end 
 * of the flexible 2D string array
 * represented by the `t_flexistr2d` structure.
 * It ensures that the array is updated
 * to include the new string.
 * The function frees `to_add` after appending it to the array.
 * 
 * @param arstr Pointer to the flexible
 *              2D string array structure (`t_flexistr2d`) 
 *              where the string will be appended.
 * @param to_add Pointer to the null-terminated
 *               string to be appended to the array.
 */
void	flexistr2d_fappend(t_flexistr2d *arstr, char *to_add);

/**
 * @brief Appends a string to a flexible 2D string array.
 * 
 * This function adds the provided string to the end 
 * of the flexible 2D string array
 * represented by the `t_flexistr2d` structure.
 * It ensures that the array is updated
 * to include the new string.
 * 
 * @param arstr Pointer to the flexible
 *              2D string array structure (`t_flexistr2d`) 
 *              where the string will be appended.
 * @param to_add Pointer to the null-terminated
 *               string to be appended to the array.
 */
void	flexistr2d_append(t_flexistr2d *arstr, char *to_add);

/**
 * @brief Frees the memory allocated for a 2D flexible
 *       string array and resets its properties.
 *
 * This function is used to safely deallocate the memory associated with a 
 * t_flexistr2d structure and reset its length to 0. It also sets the pointer 
 * to NULL to prevent dangling references.
 *
 * @param arstr A pointer to the t_flexistr2d structure to be closed.
 *              This structure contains a 2D array of strings and its length.
 *
 * @return Always returns NULL.
 */
void	*flexistr2d_close(t_flexistr2d *arstr);

/**
 * flexistr2d_add - Adds a string to a flexible 2D
 * string array at a specified position.
 *
 * @param arstr: Pointer to the flexible 2D string array (t_flexistr2d)
 *          where the string will be added.
 * @param to_add: The string to be added to the array.
 * @param n: The position in the array where the string should be inserted.
 *      If the position is out of bounds,
 *     it will be normalized to fit within the valid range.
 *
 * This function adds a new string to the flexible 2D
 *         string array at the specified position `n`.
 * If the array needs reallocation to accommodate the new string,
 *           the function ensures that
 * reallocation is performed. The function also shifts existing strings
 *     in the array to make
 * space for the new string. If `to_add` or `arstr` is NULL,
 *   or if reallocation is not needed,
 * the function returns without performing any operation.
 *
 * Note:
 * - The function assumes that `flexistr2d_need_realloc`
 *   checks whether reallocation is required.
 * - The function uses `ft_normalize` to adjust the position `n`
 *       to a valid range.
 * - The function duplicates the string `to_add` using `ft_strdup`
 *     before adding it to the array.
 */
void	flexistr2d_add(t_flexistr2d *arstr, char *to_add, int n);

/**
 * flexistr2d_add - Adds a string to a flexible 2D
 * string array at a specified position.
 *
 * @param arstr: Pointer to the flexible 2D string array (t_flexistr2d)
 *          where the string will be added.
 * @param to_add: The string to be added to the array.
 * @param n: The position in the array where the string should be inserted.
 *      If the position is out of bounds,
 *     it will be normalized to fit within the valid range.
 *
 * This function adds a new string to the flexible 2D
 *         string array at the specified position `n`.
 * If the array needs reallocation to accommodate the new string,
 *           the function ensures that
 * reallocation is performed. The function also shifts existing strings
 *     in the array to make
 * space for the new string. If `to_add` or `arstr` is NULL,
 *   or if reallocation is not needed,
 * the function returns without performing any operation. The function
 * also frees the `to_add` string after adding it to the array.
 *
 * Note:
 * - The function assumes that `flexistr2d_need_realloc`
 *   checks whether reallocation is required.
 * - The function uses `ft_normalize` to adjust the position `n`
 *       to a valid range.
 * - The function duplicates the string `to_add` using `ft_strdup`
 *     before adding it to the array.
 */
void	flexistr2d_fadd(t_flexistr2d *arstr, char *to_add, int n);

/**
 * flexistr2d_need_realloc - Checks if a reallocation is needed for a flexible
 *                  2D string array and performs the reallocation if necessary.
 *
 * @param arstr: A pointer to the t_flexistr2d structure
 *               representing the flexible 2D string array.
 *
 * This function determines if the current allocation size of the flexible
 * 2D string array is sufficient to accommodate additional data. If the
 * current length plus one exceeds or equals the allocated size, the function
 * attempts to reallocate the array with double the current allocation size.
 *
 * Return:
 * - true: If no reallocation is needed or if the reallocation is successful.
 * - false: If the input structure is invalid or if the reallocation fails.
 */
bool	flexistr2d_need_realloc(t_flexistr2d *arstr);

char	*flexistr2d_pop(t_flexistr2d *arstr);

char	*flexistr2d_npop(t_flexistr2d *arstr, int n);

void	flexistr2d_remove(t_flexistr2d *arstr, int n);

void	flexistr2d_swap(t_flexistr2d *arstr, int src, int dest);

void	flexistr2d_move(t_flexistr2d *arstr, int src, int dest);

void	flexistr2d_joinflex(t_flexistr2d *arstr1, t_flexistr2d *arstr2);

void	flexistr2d_fjoinstr(t_flexistr2d *arstr, char **str);

void	flexistr2d_joinstr(t_flexistr2d *arstr, char **str);

void	flexistr2d_reverse(t_flexistr2d *arstr);

void	flexistr2d_replace(t_flexistr2d *arstr, char *replace, int n);

void	flexistr2d_dup(t_flexistr2d *src, t_flexistr2d *dest);

void	flexistr2d_joinflexn(t_flexistr2d *arstr1, t_flexistr2d *arstr2, int n);

void	flexistr2d_fjoinstrn(t_flexistr2d *arstr, char **str, int n);

void	flexistr2d_joinstrn(t_flexistr2d *arstr, char **str, int n);

int		flexistr2d_find(t_flexistr2d *arstr, char *pattern);

void	flexistr2d_rempattern(t_flexistr2d *arstr, char *pattern);

int		flexistr2d_count(t_flexistr2d *arstr, char *pattern);

char	*flexistr2d_get(t_flexistr2d *arstr, int pos);

#endif
