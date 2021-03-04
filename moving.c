/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:37:01 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 17:37:03 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	moving_up_down(int keycode, t_config *all)
{
	float	step_x;
	float	step_y;

	step_x = cos(all->player->dir);
	step_y = sin(all->player->dir);
	if (keycode == KEY_W)
	{
		all->player->y += step_y * RATIO;
		all->player->x += step_x * RATIO;
	}
	if (keycode == KEY_S)
	{
		all->player->y -= step_y * RATIO;
		all->player->x -= step_x * RATIO;
	}
}

static void	moving_left_right(int keycode, t_config *all)
{
	if (keycode == KEY_A)
	{
		all->player->x += cos(all->player->dir - PI_2) * RATIO;
		all->player->y += sin(all->player->dir - PI_2) * RATIO;
	}
	if (keycode == KEY_D)
	{
		all->player->x -= cos(all->player->dir - PI_2) * RATIO;
		all->player->y -= sin(all->player->dir - PI_2) * RATIO;
	}
}

static void	moving_turn(int keycode, t_config *all)
{
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
}

int			moving(int keycode, t_config *config)
{
	if (keycode == ESC_KEY)
		exit(0);
	moving_turn(keycode, config);
	moving_up_down(keycode, config);
	moving_left_right(keycode, config);
	start_drawing(config);
	return (0);
}
