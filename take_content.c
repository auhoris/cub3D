/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:00:00 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 17:00:01 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	empty_lines_in_map(char *line)
{
	static int	digit_f;
	int			j;

	j = -1;
	while (line[++j] == ' ')
		;
	if (digit_f == 1 && line[j] == '\0')
		return (ERROR);
	if (in_set("0123", line[j]))
		digit_f = 1;
	return (OK);
}

static int	fill_content(t_config *all, char *line)
{
	static int	i;
	int			j;
	int			k;

	j = -1;
	while (line[++j] == ' ')
		;
	if (line[j] != '\0')
	{
		if ((all->content[i++] = ft_strdup(line)) == NULL)
			return (ERROR);
	}
	return (OK);
}

int			take_content(t_config *all, int fd)
{
	char	*line;
	int		gnl;

	if ((all->content = set_array_to_null(all->size)) == NULL)
		return (ERROR);
	line = NULL;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (fill_content(all, line) != OK
				|| empty_lines_in_map(line) != OK)
		{
			ft_free(line);
			return (ERROR);
		}
		ft_free(line);
	}
	if (gnl == -1)
		return (ERROR);
	ft_free(line);
	return (OK);
}
