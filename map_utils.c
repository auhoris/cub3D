/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:10:41 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 17:12:38 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_width(t_config *all)
{
	int	width;
	int	y;

	width = 0;
	y = -1;
	while (++y < all->map_h)
		if (width < ft_strlen(all->map[y]))
			width = ft_strlen(all->map[y]);
	return (width);
}

int	ulb(t_config *all, int x, int flag)
{
	int	y;

	if (flag == 1)
	{
		y = all->map_h - 1;
		while (all->map[y][x] != '1')
			y--;
		return (y);
	}
	else
	{
		y = 0;
		while (all->map[y][x] != '1')
			y++;
		return (y);
	}
}

int	rbd(t_config *all, int y, int flag)
{
	int	x;

	if (flag == 1)
	{
		x = ft_strlen(all->map[y]) - 1;
		while (all->map[y][x] == ' ')
			x--;
		return (x);
	}
	else
	{
		x = 0;
		while (all->map[y][x] == ' ')
			x++;
		return (x);
	}
}
