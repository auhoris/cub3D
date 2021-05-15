/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 12:25:08 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:26:10 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

static char	*spaces(char *dst, char *src, int max_l)
{
	int		d;
	char	*tmp;

	d = -1;
	while (++d < max_l - (int)ft_strlen(src))
	{
		tmp = dst;
		if ((dst = ft_strjoin(dst, " ")) == NULL)
			return (NULL);
		ft_free(tmp);
	}
	return (dst);
}

void		free_content(t_cub *all)
{
	int	i;

	i = -1;
	if (all->content != NULL)
	{
		while (all->content[++i])
		{
			free(all->content[i]);
			all->content[i] = NULL;
		}
		free(all->content);
		all->content = NULL;
	}
}

int			make_map(t_cub *all, char **map)
{
	int	i;
	int	max_l;

	max_l = 0;
	if ((all->map = set_array_to_null(all->size - MAIN_ARGC)) == NULL)
		return (ERROR);
	i = -1;
	while (map[++i])
	{
		if ((all->map[i] = ft_strdup(map[i])) == NULL)
			return (ERROR);
		max_l = max_l < (int)ft_strlen(map[i]) ? ft_strlen(map[i]) : max_l;
	}
	all->max_l = max_l;
	i = -1;
	while (map[++i])
	{
		if ((all->map[i] = spaces(all->map[i], map[i], max_l)) == NULL)
			return (ERROR);
	}
	free_content(all);
	return (OK);
}
