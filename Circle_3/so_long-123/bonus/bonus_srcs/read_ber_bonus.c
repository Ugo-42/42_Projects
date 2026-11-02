/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ber.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:24:54 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/05 09:05:18 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	fill_line(t_objs **grid, char *line, size_t line_len)
{
	size_t			x;

	*grid = malloc(sizeof(t_objs) * line_len - 1);
	if (!*grid)
		ft_exit_error(1, "In 'fill_line': " BAD_ALLOC);
	x = 0;
	while (line[x] != '\n')
	{
		(*grid)[x] = line[x];
		x++;
	}
}

static bool	realloc_grid(t_data *data)
{
	t_map	*map;

	map = &data->map;
	map->grid = ft_realloc(map->grid, map->alloc_size * sizeof(t_objs *),
			map->alloc_size * map->alloc_size * sizeof(t_objs *));
	if (!map->grid)
		ft_exit_error(1, "In 'realloc_grid': " BAD_ALLOC);
	map->alloc_size *= map->alloc_size;
	return (true);
}

static void	process_line(t_data *data, char *line)
{
	t_map	*map;

	map = &data->map;
	if (map->height == map->alloc_size && !realloc_grid(data))
		ft_exit_error(1, "In 'process_line': " BAD_ALLOC);
	if (ft_strlen(line) != map->width)
	{
		free(line);
		ft_cexit_error(1, "Map is not rectangle.", cleanup, data);
	}
	fill_line(&map->grid[map->height++], line, map->width);
	free(line);
	if (map->height > MAX_HEIGHT)
	{
		ft_cexit_error(1, "Map too high.", cleanup, data);
	}
}

static void	fill_map(t_data *data)
{
	char	*line;
	t_map	*map;

	map = &data->map;
	map->height = 0;
	line = get_next_line(data->ber_file_fd);
	if (!line)
		ft_cexit_error(1, "In 'fill_map': " BAD_ALLOC, cleanup, data);
	map->width = ft_strlen(line);
	if (map->width > MAX_WIDTH + 1)
	{
		free(line);
		ft_cexit_error(1, "Map too long.", cleanup, data);
	}
	while (line)
	{
		process_line(data, line);
		line = get_next_line(data->ber_file_fd);
	}
}

void	read_ber_file(t_data *data, char *ber)
{
	data->ber_file_fd = open(ber, O_RDONLY);
	if (data->ber_file_fd == -1)
		ft_exit_error(1, "In 'read_ber_file': " BAD_OPEN);
	data->map.alloc_size = 16;
	data->map.grid = malloc(data->map.alloc_size * sizeof(t_objs *));
	if (!data->map.grid)
		ft_exit_error(1, "In 'read_ber_file': " BAD_ALLOC);
	fill_map(data);
	data->map.width--;
	close(data->ber_file_fd);
	data->ber_file_fd = -1;
}
