/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:16:08 by vvalenti          #+#    #+#             */
/*   Updated: 2025/08/26 11:40:30 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_wall(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (ft_is_not_in_set(data->map.map[i][j], "0NSEWD"))
				continue ;
			if (!data->map.map[i][j + 1]
				|| ft_is_in_set(data->map.map[i][j + 1], " \n"))
				return (0);
			if (j == 0 || ft_is_in_set(data->map.map[i][j - 1], " \n"))
				return (0);
			if (i >= data->map.height || j > data->map.len[i + 1]
				|| ft_is_in_set(data->map.map[i + 1][j], " \n"))
				return (0);
			if (i == 0 || j > data->map.len[i - 1]
				|| ft_is_in_set(data->map.map[i - 1][j], " \n"))
				return (0);
		}
	}
	return (1);
}

static int	check_char(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (ft_is_not_in_set(data->map.map[i][j], " 01NSEWD\n"))
			{
				return (ft_fprintf(2, "line %d: column %d: Unexpected char '%c'"
						" in map\n", i + 1, j + 1, data->map.map[i][j]), 0);
			}
			if (ft_is_in_set(data->map.map[i][j], "NSEW"))
			{
				if (data->player.view)
					return (0);
				data->player.x = j;
				data->player.y = i;
				data->player.view = data->map.map[i][j];
			}
		}
	}
	return (1);
}

int	check_map(t_data *data)
{
	if (!check_char(data))
		ft_cexit_error(1, "Invalid map: only accept `0`"
			", `1` and `N`, `S`, `E` or `W` only once for the player",
			cleanup, data);
	if (!data->player.view)
		ft_cexit_error(1, "Player position needed", cleanup, data);
	if (!check_wall(data))
		ft_cexit_error(1, "Map wall incorect, need to be framed by wall",
			cleanup, data);
	return (1);
}
