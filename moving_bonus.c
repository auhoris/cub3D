/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:48:02 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/10 17:04:47 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moving_up_down(int keycode, t_config *all)
{
	t_floatp	st;
	t_floatp	pl;

	st.x = cos(all->player->dir) * DIV;
	st.y = sin(all->player->dir) * DIV;
	pl.x = all->player->x / SCALE;
	pl.y = all->player->y / SCALE;
	if (keycode == KEY_W)
	{
		if (all->map[(int)(pl.y + st.y)][(int)pl.x] != '1')
			all->player->y += st.y * MULT;
		if (all->map[(int)pl.y][(int)(pl.x + st.x)] != '1')
			all->player->x += st.x * MULT;
	}
	if (keycode == KEY_S)
	{
		if (all->map[(int)(pl.y - st.y)][(int)pl.x] != '1')
			all->player->y -= st.y * MULT;
		if (all->map[(int)pl.y][(int)(pl.x - st.x)] != '1')
			all->player->x -= st.x * MULT;
	}
}

void	moving_left_right(int keycode, t_config *all)
{
	t_floatp	st;
	t_floatp	pl;

	st.x = cos(all->player->dir - PI_2) * DIV;
	st.y = sin(all->player->dir - PI_2) * DIV;
	pl.x = all->player->x / SCALE;
	pl.y = all->player->y / SCALE;
	if (keycode == KEY_A)
	{
		if (all->map[(int)pl.y][(int)(pl.x + st.x)] != '1')
			all->player->x += st.x * MULT;
		if (all->map[(int)(pl.y + st.y)][(int)pl.x] != '1')
			all->player->y += st.y * MULT;
	}
	if (keycode == KEY_D)
	{
		if (all->map[(int)pl.y][(int)(pl.x - st.x)] != '1')
			all->player->x -= st.x * MULT;
		if (all->map[(int)(pl.y - st.y)][(int)pl.x] != '1')
			all->player->y -= st.y * MULT;
	}
}

int		moving(int keycode, t_config *all)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == TURN_LEFT_KEY)
	{
		all->player->dir -= 0.1;
		if (all->player->dir < 0)
			all->player->dir += TWO_PI;
	}
	if (keycode == TURN_RIGHT_KEY)
	{
		all->player->dir += 0.1;
		if (all->player->dir > TWO_PI)
			all->player->dir -= TWO_PI;
	}
	moving_up_down(keycode, all);
	moving_left_right(keycode, all);
	start_drawing(all);
	return (0);
}
