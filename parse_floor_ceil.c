/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:06:20 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 21:29:01 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

static int	handle_check(char **split)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (split[++i])
	{
		if ((tmp = ft_strtrim(split[i], " ")) == NULL)
			return (ERROR);
		j = -1;
		while (tmp[++j])
		{
			if (!ft_isdigit(tmp[j]))
			{
				ft_free(tmp);
				return (ERROR);
			}
		}
		ft_free(tmp);
	}
	return (OK);
}

static int	check_commas(char *line, char id)
{
	int		i;
	char	**split;

	i = -1;
	while (line[++i] == id || line[i] == ' ')
		;
	if ((split = ft_split(&line[i], ',')) == NULL)
		return (ERROR);
	if (array_lenght(split) != 3)
	{
		free_split(split);
		return (ERROR);
	}
	if (handle_check(split) != OK)
	{
		free_split(split);
		return (ERROR);
	}
	free_split(split);
	return (OK);
}

static int	valid_line(char *line, char id)
{
	int	i;
	int	c;

	i = -1;
	while (line[++i] != id)
		if (in_set("0123456789,", line[i]))
			return (ERROR);
	while (line[++i])
		if (!in_set("0123456789, ", line[i]))
			return (ERROR);
	i = -1;
	c = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			c++;
	}
	if (c != 2)
		return (ERROR);
	return (OK);
}

static int	find_line(t_cub *all, char id)
{
	int	i;
	int	j;
	int	f;

	i = -1;
	f = 0;
	while (all->content[++i] && f != 1)
	{
		j = -1;
		while (all->content[i][++j])
		{
			if (all->content[i][j] == id)
				return (i);
		}
	}
	return (OK);
}

int			parse_ceil_floor(t_cub *all, char id)
{
	int		n;
	int		color;
	char	*line;

	line = NULL;
	n = find_line(all, id);
	if ((line = ft_strdup(all->content[n])) == NULL)
		return (ERROR);
	if (valid_line(line, id) != OK || check_commas(line, id) != OK)
	{
		ft_free(line);
		return (ERROR);
	}
	if ((color = make_color(line)) == ERROR)
	{
		ft_free(line);
		return (ERROR);
	}
	if (id == 'C')
		all->args->ceil_c = color;
	if (id == 'F')
		all->args->floor_c = color;
	ft_free(line);
	return (OK);
}
