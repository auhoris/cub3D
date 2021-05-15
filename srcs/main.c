/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:16:12 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:27:11 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_cub		all;
	t_args		params;
	t_player	player;

	init_params(&params);
	init_player(&player);
	init_all(&all);
	all.args = &params;
	all.player = &player;
	if (argc == 2 || argc == 3)
	{
		if (argc == 3 && ft_strlen(argv[2]) == 6)
		{
			if (!ft_strncmp("--save", argv[2], 6))
				all.save = 1;
			else
				print_error(&all);
		}
		else if (argc == 3 && ft_strlen(argv[2]) != 6)
			print_error(&all);
		start(&all, argv[1]);
	}
	else
		ft_putendl_fd("Error\nInvalid arguments", 2);
	return (0);
}
