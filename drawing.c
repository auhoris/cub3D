/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:17:52 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 21:47:32 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

void	draw_ceil_floor(t_cub *all, float start, float end, int x)
{
	float	y;

	y = 0;
	while (y < start)
	{
		pixel_put(all->win, x, y, all->args->ceil_c);
		y++;
	}
	y = end;
	while (y < all->args->res_y)
	{
		pixel_put(all->win, x, y, all->args->floor_c);
		y++;
	}
}

t_text	fix_text(t_cub *all, t_win *img, t_text text)
{
	text.tx = all->hit == 0 ? all->inter.x -
		(int)all->inter.x : all->inter.y - (int)all->inter.y;
	text.ty = text.ty_off * text.ty_step;
	text.tx *= img->img_width;
	text.tx = (all->hit == 0 && all->ra < PI) ?
		img->img_width - text.tx : text.tx;
	text.tx = (all->hit == 1 && all->ra > PI_2 && all->ra < PI3_2) ?
		img->img_width - text.tx : text.tx;
	return (text);
}

void	draw_wall(t_cub *all,
		t_win *img, float h, int x)
{
	t_text	text;
	int		start;
	int		end;
	float	res_y;

	res_y = (float)all->args->res_y;
	start = (res_y / 2 - h / 2) < 0 ? 0 : (res_y / 2 - h / 2);
	end = (res_y / 2 + h / 2) > all->args->res_y
		? all->args->res_y : (res_y / 2 + h / 2);
	text.ty_step = img->img_height / (h);
	text.ty_off = 0;
	if (h > res_y)
		text.ty_off = (h - res_y) / 2.0;
	text = fix_text(all, img, text);
	while (start < end)
	{
		text.clr = get_color(img, (int)text.tx, (int)text.ty);
		if (text.clr != 0)
			pixel_put(all->win, x, start, text.clr);
		text.ty += text.ty_step;
		start++;
	}
}
