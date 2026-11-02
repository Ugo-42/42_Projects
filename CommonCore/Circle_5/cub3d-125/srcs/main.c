/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvalenti <vvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:20:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/06/27 14:20:16 by vvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		print_usage();
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	if (!parsing(argv[1], &data))
		return (1);
	if (!init_data(&data))
		return (1);
	cub3d(&data);
	cleanup(&data);
	return (0);
}
