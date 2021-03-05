/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_ceil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:06:20 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/05 21:34:24 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

static int	check_commas(char *line, char id)
{
	int	i;
	int	d_f;

	i = -1;
	d_f = 0;
	while (line[++i])
	{
		if (in_set("0123456789", line[i]) && d_f == 0)
		{
			d_f = 1;
			while (in_set("0123456789", line[i]))
				i++;
		}
		else if (line[i] == ',' && d_f == 1)
			d_f = 0;
		else if (line[i] == ',' && d_f == 0)
			return (ERROR);
	}
	return (OK);
}

static int	count_digits(char *line)
{
	int	i;
	int	d_cnt;
	int	d_f;

	i = -1;
	d_f = 0;
	d_cnt = 0;
	while (line[++i])
	{
		if (in_set("0123456789", line[i]) && d_f != 1)
		{
			d_f = 1;
			d_cnt++;
		}
		else if (!in_set("0123456789", line[i]) && d_f == 1)
			d_f = 0;
	}
	return (d_cnt);
}

static int	valid_line(char *line, char id)
{
	int	i;
	int	d_cnt;
	int	c_cnt;

	i = -1;
	while (line[++i] != '\0')
		if (!in_set(" 0123456789,", line[i]) && line[i] != id)
			return (ERROR);
	i = -1;
	c_cnt = 0;
	while (line[++i])
		if (line[i] == ',')
			c_cnt++;
	d_cnt = count_digits(line);
	if (c_cnt != 2 || d_cnt != 3)
		return (ERROR);
	return (OK);
}

static int	find_line(t_config *all, char id)
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

int			parse_ceil_floor(t_config *all, char **split, char id)
{
	int		n;
	int		color;
	char	*line;

	line = NULL;
	n = find_line(all, id);
	if ((line = ft_strdup(all->content[n])) == NULL)
		return (ERROR);
	if (valid_line(line, id) == ERROR)
		return (ERROR);
	if (check_commas(line, id) == ERROR)
		return (ERROR);
	if ((color = make_color(all, line)) == ERROR)
		return (ERROR);
	if (id == 'C')
		all->args->ceil_c = color;
	else if (id == 'F')
		all->args->floor_c = color;
	ft_free(line);
	return (OK);
}
