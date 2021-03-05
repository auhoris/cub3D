/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:19:15 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/05 21:55:07 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	init_window(t_config *all)
{
	t_win	win;

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx,
			all->args->res_x, all->args->res_y, "CUB3D");
	win.img = mlx_new_image(win.mlx, all->args->res_x, all->args->res_y);
	win.addres = mlx_get_data_addr(win.img,
			&win.bbp, &win.line_length, &win.endian);
	all->win = &win;
}

void		start_drawing(t_config *all)
{
	t_win	*win;
	t_win	wall[4];

	win = all->win;
	win->img = mlx_new_image(win->mlx, all->args->res_x, all->args->res_y);
	win->addres = mlx_get_data_addr(win->img,
			&win->bbp, &win->line_length, &win->endian);
	all->z_buffer = malloc(sizeof(*all->z_buffer) * (all->args->res_x + 1));
	all->d = ((float)all->args->res_x / 2) * (1 / tanf(FOV / 2));
	wall[0] = make_image(all, all->args->so_text);
	wall[1] = make_image(all, all->args->no_text);
	wall[2] = make_image(all, all->args->we_text);
	wall[3] = make_image(all, all->args->ea_text);
	precalc_drawing(all, wall);
	prep_sprites(all);
	if (all->save == 0)
	{
		mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
		mlx_destroy_image(win->mlx, win->img);
	}
}

void		start(t_config *all, char *argv)
{
	start_parsing(argv, all);
	init_window(all);
	start_drawing(all);
	if (all->save == 1)
		make_bmp(all);
	mlx_hook(all->win->win, 2, (1L << 0), moving, all);
	mlx_hook(all->win->win, 17, (1L << 0), mouse, all);
	mlx_loop(all->win->mlx);
}
