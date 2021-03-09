/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:16:12 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/09 20:01:53 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_config	all;
	t_args		params;
	t_player	player;

	init_params(&params);
	init_player(&player);
	init_all(&all);
	all.args = &params;
	all.player = &player;
	if (argc == 2 || argc == 3)
	{
		if (argc == 3 && !ft_strncmp("--save", argv[2], ft_strlen(argv[2])))
			all.save = 1;
		else if (argc == 3 && ft_strncmp("--save", argv[2], ft_strlen(argv[2])))
		{
			ft_putendl_fd("Error\nInvalid arguments", 2);
			exit(1);
		}
		start(&all, argv[1]);
	}
	else
		ft_putendl_fd("Error\nInvalid arguments", 2);
	return (0);
}
