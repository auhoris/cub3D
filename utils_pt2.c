/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:35:46 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 17:35:48 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	fix_angle(float pl_a, float lower, float upper)
{
	if (pl_a < lower)
		pl_a += TWO_PI;
	if (pl_a > upper)
		pl_a -= TWO_PI;
	return (pl_a);
}

char	**set_array_to_null(int size)
{
	int		i;
	char	**array;

	array = NULL;
	if (!(array = malloc(sizeof(*array) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i < size)
		array[i] = NULL;
	array[i] = NULL;
	return (array);
}

int		get_color(t_win *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addres + (y * data->line_length + x * (data->bbp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addres + (y * win->line_length + x * (win->bbp / 8));
	*(unsigned int*)dst = color;
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
