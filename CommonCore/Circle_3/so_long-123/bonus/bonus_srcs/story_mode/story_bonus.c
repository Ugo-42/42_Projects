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

void	so_story(t_data *data)
{
	data->days = 42 + rand() % (90 - 42);
	if (data->story)
		so_long(data, STORY_MAP_1);
	data->days = 42 + rand() % (90 - 42);
	if (data->story)
		so_long(data, STORY_MAP_2);
	data->days = 42 + rand() % (90 - 42);
	if (data->story)
		so_long(data, STORY_MAP_3);
	if (data->story)
	{
		ft_printf(BOLD GREEN "Congratulations, you are now a certified "
			"devlopper !\n" RESET_COLOR);
	}
	else
	{
		ft_printf(BOLD RED "You were absorbed by the black hole !\n"
			RESET_COLOR);
	}
	exit(0);
}
