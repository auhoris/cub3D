/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:34:23 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 19:45:09 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int			set_playerpos(t_cub *config)
{
	t_point	p;
	int		pldup_f;

	p.y = -1;
	pldup_f = 0;
	while (config->map[++p.y])
	{
		p.x = -1;
		while (config->map[p.y][++p.x])
		{
			if (in_set("NESW", config->map[p.y][p.x]))
			{
				config->player->x = (p.x + 0.5) * SCALE;
				config->player->y = (p.y + 0.5) * SCALE;
				pldup_f++;
			}
		}
	}
	if (pldup_f != 1)
		return (ERROR);
	set_playerdir(config);
	return (OK);
}
