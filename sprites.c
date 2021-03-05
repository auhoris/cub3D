/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:53:56 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/05 20:47:49 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

static t_sprite	*sort_sprites(t_config *all, t_sprite *spr)
{
	int			i;
	t_sprite	tmp;

	i = 0;
	while (i < all->sprites)
	{
		if (spr[i + 1].dist > spr[i].dist && i < all->sprites - 1)
		{
			tmp = spr[i];
			spr[i] = spr[i + 1];
			spr[i + 1] = tmp;
			i = 0;
			continue;
		}
		i++;
	}
	return (spr);
}

static t_sprite	*set_sprites(t_config *all, t_floatp pl)
{
	t_sprite	*a;
	int			x;
	int			y;
	int			i;

	if (!(a = malloc(sizeof(*a) * (all->sprites + 1))))
		return (NULL);
	y = -1;
	i = 0;
	while (all->map[++y])
	{
		x = -1;
		while (all->map[y][++x])
		{
			if (all->map[y][x] == '2')
			{
				a[i].x = x + 0.5;
				a[i].y = y + 0.5;
				a[i].img = make_image(all, all->args->sprite);
				a[i].dist = kostil(a[i].x, a[i].y, pl);
				i++;
			}
		}
	}
	return (a);
}

static void		handle_drawing(t_config *all,
		t_sprite arr, float mid_s, float res_y)
{
	int		start;
	int		end;
	int		obj_col;
	int		clr;

	start = (res_y - arr.s_h) / 2.0 < 0 ? 0 : (res_y - arr.s_h) / 2.0;
	end = (res_y + arr.s_h) / 2.0 > res_y ? res_y : (res_y + arr.s_h) / 2.0;
	arr.s_off = arr.s_h > res_y ? (arr.s_h - res_y) / 2.0 : 0;
	arr.s_step = arr.img.img_height / arr.s_h;
	arr.s_y = arr.s_step * arr.s_off;
	while (start < end)
	{
		clr = get_color(&arr.img, arr.s_x
				/ arr.s_w * arr.img.img_width, arr.s_y);
		obj_col = (int)(mid_s + arr.s_x - (arr.s_w / 2));
		if (obj_col >= 0 && obj_col <= all->args->res_x && clr != -16777216)
			if (all->z_buffer[obj_col] >= arr.dist)
				pixel_put(all->win, obj_col, start, clr);
		arr.s_y += arr.s_step;
		start++;
	}
}

static void		draw_sprites(t_config *all, t_sprite arr, float obj_angle)
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

void			prep_sprites(t_config *all)
{
	t_sprite	*arr;
	t_floatp	pl;
	int			i;
	float		obj_angle;

	pl.x = all->player->x / SCALE;
	pl.y = all->player->y / SCALE;
	arr = set_sprites(all, pl);
	arr = sort_sprites(all, arr);
	i = -1;
	while (++i < all->sprites)
	{
		obj_angle = atan2f(sinf(all->player->dir), cosf(all->player->dir))
			- atan2f(arr[i].y - pl.y, arr[i].x - pl.x);
		obj_angle = fix_angle(obj_angle, -PI, PI);
		if (fabsf(obj_angle) < (FOV / 2) && arr[i].dist > 0.1f)
		{
			arr[i].s_h = all->d / arr[i].dist;
			arr[i].s_w = arr[i].s_h /
				((float)arr[i].img.img_height / (float)arr[i].img.img_width);
			draw_sprites(all, arr[i], obj_angle);
		}
	}
	ft_free(arr);
	ft_free(all->z_buffer);
}
