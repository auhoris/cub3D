/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:16:07 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:28:41 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/_types/_errno_t.h>

void		free_check(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void		mlx_check_destroy(void *mlx, void *ptr)
{
	if (ptr)
	{
		mlx_destroy_image(mlx, ptr);
		ptr = 0;
	}
}

static int	handle_checking(char **split)
{
	int		i;
	int		j;
	char	*tmp;

	j = -1;
	while (split[++j])
	{
		tmp = ft_strtrim(split[j], " ");
		i = -1;
		while (tmp[++i] == '0')
			;
		if (ft_strlen(&tmp[i]) > 3)
		{
			ft_free(tmp);
			return (ERROR);
		}
		ft_free(tmp);
	}
	return (OK);
}

int			make_color(char *line)
{
	int		i;
	int		rgb[3];
	char	**split;

	i = -1;
	while (!in_set("0123456789", line[++i]))
		;
	if ((split = ft_split(&line[i], ',')) == NULL)
		return (ERROR);
	if (handle_checking(split) != OK)
	{
		free_split(split);
		return (ERROR);
	}
	i = -1;
	while (split[++i])
		rgb[i] = ft_atoi(split[i]);
	free_split(split);
	i = -1;
	while (++i < 3)
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ERROR);
	return (create_trgb(1, rgb[0], rgb[1], rgb[2]));
}
