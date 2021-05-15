/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_parameters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:00:47 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:28:09 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static char	*handle_texture(char *line, char *text)
{
	char	*new_line;

	new_line = NULL;
	while (in_set(text, *line) || *line == ' ')
		line++;
	return ((new_line = ft_strdup(line)) == NULL ? NULL : new_line);
}

static int	parse_other(t_cub *all, char **split, char *line)
{
	int	hold_error;

	while (*line == ' ')
		line++;
	hold_error = OK;
	if (ft_strnstr("R", split[0], 1) &&
			(all->args->res_x == -1 || all->args->res_y == -1))
		hold_error = parse_resol(all, split);
	else if (ft_strnstr("C", split[0], 1) && all->args->ceil_c == -1)
		hold_error = parse_ceil_floor(all, 'C');
	else if (ft_strnstr("F", split[0], 1) && all->args->floor_c == -1)
		hold_error = parse_ceil_floor(all, 'F');
	else if (!ft_strncmp("S", line, 1) && all->args->sprite == NULL)
	{
		if ((all->args->sprite = handle_texture(line, "S")) == NULL)
			return (ERROR);
	}
	else
		return (ERROR);
	return (hold_error);
}

static int	parse_textures(t_cub *all, char *line)
{
	while (*line == ' ')
		line++;
	if (!ft_strncmp("NO", line, 2) && all->args->no_text == NULL)
	{
		if ((all->args->no_text = handle_texture(line, "NO")) == NULL)
			return (ERROR);
	}
	else if (!ft_strncmp("SO", line, 2) && all->args->so_text == NULL)
	{
		if ((all->args->so_text = handle_texture(line, "SO")) == NULL)
			return (ERROR);
	}
	else if (!ft_strncmp("WE", line, 2) && all->args->we_text == NULL)
	{
		if ((all->args->we_text = handle_texture(line, "WE")) == NULL)
			return (ERROR);
	}
	else if (!ft_strncmp("EA", line, 2) && all->args->ea_text == NULL)
	{
		if ((all->args->ea_text = handle_texture(line, "EA")) == NULL)
			return (ERROR);
	}
	else
		return (ERROR);
	return (OK);
}

int			parsing_parameters(t_cub *all)
{
	char	**split;
	int		i;
	int		e_code;

	i = -1;
	split = NULL;
	e_code = OK;
	while (++i < MAIN_ARGC)
	{
		if ((split = ft_split(all->content[i], ' ')) == NULL)
			return (ERROR);
		if (ft_strlen(split[0]) == 2)
			e_code = parse_textures(all, all->content[i]);
		else if (ft_strlen(split[0]) == 1)
			e_code = parse_other(all, split, all->content[i]);
		else
		{
			free_split(split);
			return (ERROR);
		}
		free_split(split);
		if (e_code != OK)
			return (ERROR);
	}
	return (make_map(all, &all->content[i]));
}
