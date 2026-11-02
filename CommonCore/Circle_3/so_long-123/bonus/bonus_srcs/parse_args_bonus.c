/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:00:00 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 12:42:49 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	print_usage(void)
{
	ft_printf("Usage: ./so_long_bonus <map>.ber\n"
		"\noptions:\n"
		"\t[-r|--random]  # genarate a random labyrinth\n"
		"\t[-s|--story]   # launch story mode\n"
		"\t[-e|--endless] # launch endless mode\n"
		"\t[-g|--genmap <width> <height> <difficulty>]\n\n");
}

static bool	is_option(const char *arg, const char *opt1, const char *opt2)
{
	return (ft_strcmp(arg, opt1) == 0 || ft_strcmp(arg, opt2) == 0);
}

void	handle_options(t_data *data, char **map_path, int argc, char **argv)
{
	if (argc < 2 || is_option(argv[1], "-h", "--help"))
	{
		print_usage();
		exit(0);
	}
	if (is_option(argv[1], "-r", "--random"))
	{
		*map_path = create_map(5 + rand() % (MAX_WIDTH - 5),
				5 + rand() % (MAX_HEIGHT - 5), 1 + rand() % 15);
	}
	else if (is_option(argv[1], "-g", "--genmap") && argc == 5)
		*map_path = create_map(ft_atoi(argv[2]),
				ft_atoi(argv[3]), ft_atoi(argv[4]));
	else if (is_option(argv[1], "-e", "--endless"))
	{
		data->endless = true;
		so_endless(data);
	}
	else if (is_option(argv[1], "-s", "--story"))
	{
		data->story = true;
		so_story(data);
	}
}
