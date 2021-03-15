/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:39:58 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 20:13:30 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	count_size(t_cub *all, int fd)
{
	int		j;
	char	*line;
	int		gnl;

	line = NULL;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		j = -1;
		while (line[++j] == ' ')
			;
		if (line[j] != '\0')
			all->size++;
		ft_free(line);
	}
	if (gnl == -1)
		return (ERROR);
	ft_free(line);
	return (all->size > 8 ? OK : ERROR);
}

void		start_parsing(char *file, t_cub *all)
{
	int	fd;
	int	e_code;

	if ((e_code = check_file(file)) != OK)
		print_error(all);
	if ((fd = open(file, O_RDONLY)) == ERROR)
		print_error(all);
	if ((e_code = count_size(all, fd)) != OK)
		print_error(all);
	close(fd);
	fd = open(file, O_RDONLY);
	if ((e_code = take_content(all, fd)) != OK)
		print_error(all);
	close(fd);
	if ((e_code = parsing_parameters(all)) != OK)
		print_error(all);
	if ((e_code = parse_map(all)) != OK)
		print_error(all);
}
