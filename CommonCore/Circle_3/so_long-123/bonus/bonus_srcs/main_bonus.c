/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:07:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/03/07 10:24:07 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	srand(time(NULL));
	data.endless = false;
	data.story = false;
	handle_options(&data, &argv[1], argc, argv);
	if (!ft_cmp_extension(argv[1], ".ber"))
		ft_fexit_error(1, ft_stringf("'%s': Not a `.ber` file", argv[1]));
	so_long(&data, argv[1]);
}
