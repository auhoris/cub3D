/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:16:07 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 21:28:19 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int			first_one(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '1')
		;
	return (i);
}

t_floatp	horizontal_hit(t_cub *all, t_floatp fp, float pl_a)
{
	t_floatp	hit;
	int			y;
	int			dir;

	y = sinf(pl_a) > 0 ? (int)ceilf(fp.y) : (int)floorf(fp.y);
	dir = sinf(pl_a) > 0 ? 1 : -1;
	hit.x = fp.x + dir * fabsf((float)y - fp.y) / tanf(pl_a);
	hit.y = fp.y + dir * fabsf((float)y - fp.y);
	while (hit.y > 0.0 && (int)hit.x < (int)ft_strlen(all->map[(int)fabsf(hit.y)])
			&& (int)hit.x > first_one(all->map[(int)(hit.y)]))
	{
		if (all->map[(int)(hit.y + dir * 0.00001)][(int)hit.x] == '1')
			return (hit);
		hit.x += dir * 1 / tanf(pl_a);
		hit.y += dir * 1;
	}
	return (hit);
}

t_floatp	vertical_hit(t_cub *all, t_floatp fp, float pl_a)
{
	t_floatp	hit;
	int			x;
	float		dir;

	x = cosf(pl_a) > 0 ? (int)ceilf(fp.x) : (int)floorf(fp.x);
	dir = cosf(pl_a) > 0 ? 1 : -1;
	hit.x = fp.x + dir * fabsf((float)x - fp.x);
	hit.y = fp.y + dir * fabsf((float)x - fp.x) * tanf(pl_a);
	while (hit.x > 0.0 && (int)hit.y > 0 && (int)hit.y < all->map_h)
	{
		if (all->map[(int)(hit.y)][(int)(hit.x + dir * 0.00001)] == '1')
			return (hit);
		hit.x += dir * 1;
		hit.y += dir * 1 * tanf(pl_a);
	}
	return (hit);
}
