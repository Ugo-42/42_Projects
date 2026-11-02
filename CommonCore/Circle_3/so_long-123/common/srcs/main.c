/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:07:57 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/25 09:55:52 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("Usage: ./so_long *.ber\n"), 1);
	if (ft_cmp_extension(argv[1], ".ber") == 0)
		ft_fexit_error(1, ft_stringf("'%s': Not a `.ber` file", argv[1]));
	so_long(argv[1]);
}
