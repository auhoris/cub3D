/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:15:20 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/02 16:49:57 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	ft_exit(char *str)
{
	ft_putstr("ERROR: ");
	ft_putstr(str);
	ft_putchar('\n');
	exit(0);
}

int		in_set(char *set, char c)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = -1;
	while (split[++i])
		if (split[i] != NULL)
			ft_free(split[i]);
	free(split);
	split = NULL;
}

int		array_lenght(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return (0);
	while (array[++i])
		;
	return (i);
}
