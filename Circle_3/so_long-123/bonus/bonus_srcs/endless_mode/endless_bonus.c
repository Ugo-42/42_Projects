/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endless.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:07:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 14:09:29 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	so_endless(t_data *data)
{
	size_t	size;
	size_t	density;
	char	*path;

	data->days = 1;
	density = 1;
	size = 7;
	while (data->endless)
	{
		path = create_map(size, size, density);
		so_long(data, path);
		size += rand() % 3 + 2;
		if (size > MAX_HEIGHT)
			size = MAX_HEIGHT;
		data->days++;
		if ((data->days % 5 == 0) && density != 20)
			density++;
	}
	exit(0);
}
