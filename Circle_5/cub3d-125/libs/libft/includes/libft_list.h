/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/21 13:40:58 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

/*┌───────┐
  │ list/ │
  └───────┘*/

/**
 * @struct s_list
 * @brief Represents a node in a singly linked list.
 *
 * @param content Pointer to the content stored in the node.
 * @param next Pointer to the next node in the list.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/**
 * @brief Counts the number of nodes in a linked list.
 * @param lst A pointer to the first node of the list.
 * @return The number of nodes in the list.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Adds a new node to the end of a linked list.
 * @param lst A pointer to the pointer of the first node of the list.
 * @param new The new node to add.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Adds a new node to the beginning of a linked list.
 * @param lst A pointer to the pointer of the first node of the list.
 * @param new The new node to add.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Deletes and frees all nodes in a linked list.
 * @param lst A pointer to the pointer of the first node of the list.
 * @param del A function to free the content of each node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief Deletes and frees a single node in a linked list.
 * @param lst A pointer to the node to delete.
 * @param del A function to free the content of the node.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Iterates through a linked list and applies a function to each node.
 * @param lst A pointer to the first node of the list.
 * @param f The function to apply to each node's content.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Returns the last node of a linked list.
 * @param lst A pointer to the first node of the list.
 * @return A pointer to the last node of the list.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Creates a new linked list by applying a function to each node of an
 *        existing list.
 * @param lst A pointer to the first node of the original list.
 * @param f The function to apply to each node's content.
 * @param del A function to free the content of a node if allocation fails.
 * @return A pointer to the first node of the new list, or NULL if allocation
 * fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief Creates a new node for a linked list.
 * @param content The content to store in the new node.
 * @return A pointer to the newly created node, or NULL if allocation fails.
 */
t_list	*ft_lstnew(void *content);

#endif
