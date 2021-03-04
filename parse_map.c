/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:09:48 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 17:10:52 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_errno_t.h>

int		validate_symbols(t_config *all)
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

int		flood_fill(t_config *all, char **map, int x, int y)
{
	if ((x == rbd(all, y, 0) || x == rbd(all, y, 1)) && map[y][x] != '1')
		return (ERROR);
	if ((y == 0 || y == all->map_h) && map[y][x] != '1')
		return (ERROR);
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

char	**map_copy(t_config *all)
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

int		check_closed(t_config *all, char **copy)
{
	int	x;
	int	y;

	y = -1;
	while (copy[++y])
	{
		x = -1;
		while (copy[y][++x])
		{
			if (copy[y][x] == '0')
			{
				if (!in_set("012NESW", copy[y][x + 1]))
					return (ERROR);
				if (!in_set("012NESW", copy[y][x - 1]))
					return (ERROR);
				if (!in_set("012NESW", copy[y + 1][x]))
					return (ERROR);
				if (!in_set("012NESW", copy[y - 1][x]))
					return (ERROR);
			}
		}
	}
	return (OK);
}

int		parse_map(t_config *all)
{
	int		e_code;
	char	**copy;

	if (validate_symbols(all) != OK)
		return (ERROR);
	all->map_h = all->size - MAIN_ARGC;
	all->map_w = set_width(all);
	if ((e_code = set_playerpos(all)) != OK)
		return (ERROR);
	if ((copy = map_copy(all)) == NULL)
		return (ERROR);
	if ((e_code = flood_fill(all, copy, (int)all->player->x
					/ SCALE, (int)all->player->y / SCALE)) != OK
		|| check_closed(all, copy) != OK)
	{
		free_split(copy);
		return (ERROR);
	}
	free_split(copy);
	return (OK);
}
