/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalc_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:22:21 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/10 17:07:33 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		calc_wall(t_config *all, float dist, int x, t_win *win)
{
	float	height;
	float	res_y;
	float	start_wall;
	float	end_wall;

	res_y = (float)all->args->res_y;
	dist = (dist < 0.1) ? 0.1 : dist;
	height = all->d / dist;
	if ((start_wall = res_y / 2 - height / 2) < 0)
		start_wall = 0;
	if ((end_wall = res_y / 2 + height / 2) > all->args->res_y)
		end_wall = all->args->res_y;
	draw_ceil_floor(all, start_wall, end_wall, x);
	draw_wall(all, win, height, x);
}

static float	calc_distance(t_config *all,
		t_floatp hor_hit, t_floatp ver_hit, t_floatp fp)
{
	float	dist_v;
	float	dist_h;

	dist_v = (ver_hit.x - fp.x) * cosf(all->player->dir)
		+ (ver_hit.y - fp.y) * sinf(all->player->dir);
	dist_h = (hor_hit.x - fp.x) * cosf(all->player->dir)
		+ (hor_hit.y - fp.y) * sinf(all->player->dir);
	all->inter = dist_h < dist_v ? hor_hit : ver_hit;
	all->hit = dist_h < dist_v ? 0 : 1;
	return (dist_h < dist_v ? dist_h : dist_v);
}

static void		handle_calc_wall(t_config *all, int x, t_win wall[])
{
	if (all->hit == 0 && (all->ra > PI))
		calc_wall(all, all->z_buffer[x], x, &wall[1]);
	else if (all->hit == 0 && (all->ra < PI))
		calc_wall(all, all->z_buffer[x], x, &wall[0]);
	else if (all->hit == 1 && (all->ra > PI_2 && all->ra < PI3_2))
		calc_wall(all, all->z_buffer[x], x, &wall[2]);
	else
		calc_wall(all, all->z_buffer[x], x, &wall[3]);
}

void			precalc_drawing(t_config *all, t_win wall[])
{
	t_floatp	fp;
	int			x;
	t_floatp	hor_hit;
	t_floatp	ver_hit;

	all->ra = all->player->dir - FOV / 2;
	fp.x = all->player->x / SCALE;
	fp.y = all->player->y / SCALE;
	x = -1;
	while (++x < all->args->res_x)
	{
		all->ra = fix_angle(all->ra, 0, TWO_PI);
		if (all->ra < PI || all->ra > PI)
			hor_hit = horizontal_hit(all, fp, all->ra);
		if ((all->ra > PI_2 && all->ra < PI3_2)
				|| (all->ra < PI_2 || all->ra > PI3_2))
			ver_hit = vertical_hit(all, fp, all->ra);
		all->z_buffer[x] = calc_distance(all, hor_hit, ver_hit, fp);
		handle_calc_wall(all, x, wall);
		all->ra += FOV / all->args->res_x;
	}
}
