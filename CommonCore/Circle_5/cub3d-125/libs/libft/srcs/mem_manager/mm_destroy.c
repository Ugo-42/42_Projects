/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:23:42 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/05/13 23:27:24 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal/mem_manager.h"

void	mm_destroy(void)
{
	internal_manager(MM_DESTROY, NULL);
}
