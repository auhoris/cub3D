/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:53:56 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 20:56:26 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static void		set_distance(t_cub *all, t_floatp pl)
{
	int	i;

	i = -1;
	while (++i < all->sprites)
	{
		all->spr[i].dist = fabsf((all->spr[i].x - pl.x) * cosf(all->player->dir)
				+ (all->spr[i].y - pl.y) * sinf(all->player->dir));
	}
}

static void		handle_drawing(t_cub *all,
		t_sprite arr, float mid_s, float res_y)
{
	int		start;
	int		end;
	int		obj_col;
	t_win	img;
	int		clr;

	img = all->wall[4];
	start = (res_y - arr.s_h) / 2.0 < 0 ? 0 : (res_y - arr.s_h) / 2.0;
	end = (res_y + arr.s_h) / 2.0 > res_y ? res_y : (res_y + arr.s_h) / 2.0;
	arr.s_off = arr.s_h > res_y ? (arr.s_h - res_y) / 2.0 : 0;
	arr.s_step = img.img_height / arr.s_h;
	arr.s_y = arr.s_step * arr.s_off;
	while (start < end)
	{
		clr = get_color(&img, arr.s_x
				/ arr.s_w * img.img_width, arr.s_y);
		obj_col = (int)(mid_s + arr.s_x - (arr.s_w / 2));
		if (obj_col >= 0 && obj_col <= all->args->res_x && clr != -16777216)
			if (all->z_buffer[obj_col] >= arr.dist)
				pixel_put(all->win, obj_col, start, clr);
		arr.s_y += arr.s_step;
		start++;
	}
}

static void		draw_sprites(t_cub *all, t_sprite arr, float obj_angle)
{
	int		clr;
	float	mid_s;
	float	res_y;

	arr.s_x = -1;
	res_y = (float)all->args->res_y;
	mid_s = all->args->res_x * (1.0f -
			(0.5f * (obj_angle / (FOV / 2.0f)) + 0.5f));
	while (++arr.s_x < arr.s_w)
		handle_drawing(all, arr, mid_s, res_y);
}

void			prep_sprites(t_cub *all)
{
	t_floatp	pl;
	int			i;
	float		obj_angle;

	pl.x = all->player->x / SCALE;
	pl.y = all->player->y / SCALE;
	set_distance(all, pl);
	quicksort(all->spr, 0, all->sprites);
	i = -1;
	while (++i < all->sprites)
	{
		obj_angle = atan2f(sinf(all->player->dir), cosf(all->player->dir))
			- atan2f(all->spr[i].y - pl.y, all->spr[i].x - pl.x);
		obj_angle = fix_angle(obj_angle, -PI, PI);
		if (fabsf(obj_angle) < (FOV / 1.3) && all->spr[i].dist > 0.1f)
		{
			all->spr[i].s_h = all->d / all->spr[i].dist;
			all->spr[i].s_w = all->spr[i].s_h /
				((float)all->wall[4].img_height / all->wall[4].img_width);
			draw_sprites(all, all->spr[i], obj_angle);
		}
	}
	free(all->z_buffer);
	all->z_buffer = NULL;
}
