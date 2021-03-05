/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:16:07 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/05 21:39:20 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	kostil(float a_x, float a_y, t_floatp pl)
{
	return (sqrtf((a_x - pl.x) * (a_x - pl.x) + (a_y - pl.y) * (a_y - pl.y)));
}

int		make_color(t_config *all, char *line)
{
	int	i;
	int	rgb[3];
	int	j;

	i = -1;
	j = 0;
	while (line[++i] != '\0' && j < 3)
	{
		if (in_set(DIGITS, line[i]) && line[i] != '\0')
		{
			rgb[j] = ft_atoi(&line[i]);
			while (in_set(DIGITS, line[i]))
				i++;
			j++;
		}
	}
	j = -1;
	while (++j < 3)
		if (rgb[j] > 255 || rgb[j] < 0)
			return (ERROR);
	return (create_trgb(1, rgb[0], rgb[1], rgb[2]));
}
