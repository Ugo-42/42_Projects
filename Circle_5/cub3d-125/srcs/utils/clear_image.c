/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:40:40 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/08/22 09:55:05 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_image(mlx_image_t *img)
{
	if (!img || !img->pixels)
		return ;
	ft_bzero(img->pixels, (img->width * img->height * sizeof(uint32_t)));
}
