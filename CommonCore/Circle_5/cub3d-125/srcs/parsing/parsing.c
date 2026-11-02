/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:17:20 by vvalenti          #+#    #+#             */
/*   Updated: 2025/08/26 11:35:01 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_assets_path(const char *s, char *assets)
{
	char	*res;

	s += ft_strlen(assets);
	ft_skip_spaces(&s);
	res = mm_strdup(s);
	res[ft_strlen(res) - 1] = '\0';
	return (res);
}

static char	*get_assets(int fd, char *s, t_data *data)
{
	while (s)
	{
		if (!ft_strncmp(s, "NO", 2))
			data->assets.no_path = get_assets_path(s, "NO");
		else if (!ft_strncmp(s, "SO", 2))
			data->assets.so_path = get_assets_path(s, "SO");
		else if (!ft_strncmp(s, "EA", 2))
			data->assets.ea_path = get_assets_path(s, "EA");
		else if (!ft_strncmp(s, "WE", 2))
			data->assets.we_path = get_assets_path(s, "WE");
		else if (!ft_strncmp(s, "F", 1))
			data->assets.f_path = get_assets_path(s, "F");
		else if (!ft_strncmp(s, "C", 1))
			data->assets.c_path = get_assets_path(s, "C");
		else if (*s != '\n')
			return (s);
		free(s);
		s = get_next_line(fd);
	}
	return (NULL);
}

static void	realloc_map(t_data *data, char *s)
{
	data->map.size *= 2;
	data->map.map = mm_recalloc(data->map.map,
			sizeof(char **) * (data->map.size));
	data->map.len = mm_realloc(data->map.len,
			sizeof (int *) * (data->map.size));
	if (!data->map.map || !data->map.len)
	{
		free(s);
		ft_cexit_error(1, BAD_ALLOC, cleanup, data);
	}
}

static void	fill_map(t_data *data, char *s, int fd)
{
	size_t	map_size;

	map_size = 0;
	while (s)
	{
		data->map.map[map_size] = mm_strdup(s);
		if (!data->map.map[map_size])
		{
			free(s);
			ft_cexit_error(1, BAD_ALLOC, cleanup, data);
		}
		data->map.len[map_size] = ft_strlen(s);
		if (data->map.len[map_size] > 0
			&& data->map.len[map_size] > data->map.width)
			data->map.width = data->map.len[map_size] - 1;
		free(s);
		s = get_next_line(fd);
		map_size++;
		if (map_size >= data->map.size)
			realloc_map(data, s);
	}
	free(s);
	data->map.height = map_size;
}

bool	parsing(const char *file, t_data *data)
{
	int		fd;
	char	*s;

	if (!ft_cmp_extension(file, ".cub"))
		return (print_error("File must have a `.cub` extension"));
	assign_default_assets(data);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_cexit_error(1, BAD_OPEN, cleanup, data);
	s = get_next_line(fd);
	if (!s)
		return (false);
	s = get_assets(fd, s, data);
	data->map.map = mm_calloc(64 * sizeof(char *));
	data->map.len = mm_alloc(64 * sizeof(int));
	if (!data->map.map || !data->map.len)
		ft_cexit_error(1, BAD_ALLOC, cleanup, data);
	data->map.size = 64;
	fill_map(data, s, fd);
	close(fd);
	if (!check_map(data))
		return (false);
	return (true);
}
