/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:19:15 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/17 16:09:49 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdlib.h>

static void	init_window(t_cub *all)
{
	t_win	*win;

	win = malloc(sizeof(*win));
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx,
			all->args->res_x, all->args->res_y, "CUB3D");
	win->img = mlx_new_image(win->mlx, all->args->res_x, all->args->res_y);
	win->addres = mlx_get_data_addr(win->img,
			&win->bbp, &win->line_length, &win->endian);
	all->win = win;
}

void		start_drawing(t_cub *all)
{
	t_win	*win;

	win = all->win;
	win->img = mlx_new_image(win->mlx, all->args->res_x, all->args->res_y);
	win->addres = mlx_get_data_addr(win->img,
			&win->bbp, &win->line_length, &win->endian);
	all->z_buffer = malloc(sizeof(*all->z_buffer) * (all->args->res_x + 1));
	all->d = ((float)all->args->res_x / 2) * (1 / tanf(FOV / 2));
	precalc_drawing(all, all->wall);
	prep_sprites(all);
	if (all->save == 0)
	{
		mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
		mlx_destroy_image(win->mlx, win->img);
	}
}

t_sprite	*parse_sprites(t_cub *all)
{
	t_sprite	*arr;
	t_point		p;

	arr = NULL;
	if ((arr = (t_sprite *)malloc(sizeof(*arr) * (all->sprites + 1))) == NULL)
		return (NULL);
	p.y = -1;
	all->sprites = 0;
	while (all->map[++p.y])
	{
		p.x = -1;
		while (all->map[p.y][++p.x])
		{
			if (all->map[p.y][p.x] == '2')
			{
				arr[all->sprites].x = p.x + 0.5;
				arr[all->sprites].y = p.y + 0.5;
				all->sprites++;
			}
		}
	}
	return (arr);
}

static void	prep_images(t_cub *all)
{
	all->spr = parse_sprites(all);
	all->wall[0] = make_image(all, all->args->so_text);
	all->wall[1] = make_image(all, all->args->no_text);
	all->wall[2] = make_image(all, all->args->we_text);
	all->wall[3] = make_image(all, all->args->ea_text);
	all->wall[4] = make_image(all, all->args->sprite);
}

void		start(t_cub *all, char *argv)
{
	start_parsing(argv, all);
	init_window(all);
	prep_images(all);
	start_drawing(all);
	if (all->save == 1)
		make_bmp(all);
	mlx_hook(all->win->win, 2, (1L << 0), moving, all);
	mlx_hook(all->win->win, 17, 0, mouse, all);
	mlx_loop(all->win->mlx);
}
