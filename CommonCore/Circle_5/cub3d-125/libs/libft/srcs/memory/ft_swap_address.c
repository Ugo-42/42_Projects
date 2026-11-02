/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_address.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:08:34 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/12/12 16:28:56 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap_address(void *a_address, void *b_address)
{
	void	*tmp;
	void	**a;
	void	**b;

	a = (void **)a_address;
	b = (void **)b_address;
	if (a && b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}
