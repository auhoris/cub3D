/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:34:23 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:28:26 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_playerdir(t_cub *all)
{
	char	dir;

	dir = all->map[(int)(all->player->y / SCALE)]
		[(int)(all->player->x / SCALE)];
	if (dir == 'N')
		all->player->dir = PI3_2;
	if (dir == 'S')
		all->player->dir = PI_2;
	if (dir == 'W')
		all->player->dir = PI;
	if (dir == 'E')
		all->player->dir = TWO_PI;
}

int			set_playerpos(t_cub *all)
{
	t_point	p;
	int		pldup_f;

	p.y = -1;
	pldup_f = 0;
	while (all->map[++p.y])
	{
		p.x = -1;
		while (all->map[p.y][++p.x])
		{
			if (in_set("NESW", all->map[p.y][p.x]))
			{
				if (p.x == 0 || p.x == (int)ft_strlen(all->map[p.y]) - 1)
					return (ERROR);
				if (p.y == 0 || p.y == all->map_h)
					return (ERROR);
				all->player->x = (p.x + 0.5) * SCALE;
				all->player->y = (p.y + 0.5) * SCALE;
				pldup_f++;
			}
		}
	}
	set_playerdir(all);
	return (pldup_f == 1 ? OK : ERROR);
}
