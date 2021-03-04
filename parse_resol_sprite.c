/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resol_sprite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:07:55 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 17:07:56 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	parse_resol(t_config *all, char **split)
{
	int	i;
	int	str;

	if (array_lenght(split) != 3)
		return (ERROR);
	i = 0;
	while (split[++i] != NULL)
	{
		str = -1;
		while (split[i][++str] != '\0')
			if (!in_set("-+0123456789", split[i][str]))
				return (ERROR);
	}
	all->args->res_x = ft_atoi(split[1]);
	all->args->res_y = ft_atoi(split[2]);
	all->args->res_x = (all->save == 0 && all->args->res_x > all->screen_width)
		? all->args->res_x = all->screen_width : all->args->res_x;
	all->args->res_y = (all->save == 0 && all->args->res_y > all->screen_height)
		? all->args->res_y = all->screen_height : all->args->res_y;
	all->args->res_x = all->args->res_x < 1 ? 640 : all->args->res_x;
	all->args->res_y = all->args->res_y < 1 ? 480 : all->args->res_y;
	return (OK);
}
