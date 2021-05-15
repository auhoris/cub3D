/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:09:48 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:27:56 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_errno_t.h>

static int		validate_symbols(t_cub *all)
{
	int	x;
	int	y;
	int	f_d;

	y = -1;
	while (all->map[++y])
	{
		x = -1;
		f_d = 0;
		while (all->map[y][++x])
		{
			if (!in_set(VALID_MAP_SYMB, all->map[y][x]))
				return (ERROR);
			if (all->map[y][x] == '2')
				all->sprites++;
		}
	}
	return (OK);
}

static int		flood_fill(t_cub *all, char **map, int x, int y)
{
	if (map[y][x] != '1' && (map[y][x] == '0' || in_set("NESW", map[y][x])))
	{
		map[y][x] = '1';
		if (flood_fill(all, map, x + 1, y) == ERROR)
			return (ERROR);
		if (flood_fill(all, map, x - 1, y) == ERROR)
			return (ERROR);
		if (flood_fill(all, map, x, y + 1) == ERROR)
			return (ERROR);
		if (flood_fill(all, map, x, y - 1) == ERROR)
			return (ERROR);
	}
	if (map[y][x] == ' ')
		return (ERROR);
	return (OK);
}

static char		**map_copy(t_cub *all)
{
	int		i;
	char	**copy;

	if ((copy = malloc(sizeof(*copy) * (all->map_h + 1))) == NULL)
		return (NULL);
	i = -1;
	while (++i < all->map_h)
	{
		if ((copy[i] = ft_strdup(all->map[i])) == NULL)
		{
			free_split(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

static int		check_closed(t_cub *all, char **copy)
{
	int	x;
	int	y;

	y = -1;
	while (copy[++y])
	{
		x = -1;
		while (copy[y][++x])
		{
			if (copy[y][x] == '0' || copy[y][x] == '2')
			{
				if (y == all->map_h - 1 || y == 0 ||
						x == (int)ft_strlen(all->map[y]) - 1 || x == 0)
					return (ERROR);
				if (!in_set("012NESW", copy[y][x + 1])
						|| !in_set("012NESW", copy[y][x - 1]))
					return (ERROR);
				if (!in_set("012NESW", copy[y + 1][x])
						|| !in_set("012NESW", copy[y - 1][x]))
					return (ERROR);
			}
		}
	}
	return (OK);
}

int				parse_map(t_cub *all)
{
	int		e_code;
	char	**copy;

	if (validate_symbols(all) != OK)
		return (ERROR);
	all->map_h = all->size - MAIN_ARGC;
	all->map_w = all->max_l;
	if ((e_code = set_playerpos(all)) != OK)
		return (ERROR);
	if ((copy = map_copy(all)) == NULL)
		return (ERROR);
	if (check_closed(all, copy) != OK || (e_code = flood_fill(all, copy,
					(int)all->player->x / SCALE,
					(int)all->player->y / SCALE)) != OK)
	{
		free_split(copy);
		return (ERROR);
	}
	free_split(copy);
	return (OK);
}
