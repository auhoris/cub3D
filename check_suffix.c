/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_suffix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:59:36 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/16 14:25:37 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *file)
{
	int	i;
	int	dot_c;

	i = -1;
	dot_c = 0;
	while (file[++i])
		if (file[i] == '.')
			dot_c++;
	i = -1;
	while (dot_c > 0)
		if (file[++i] == '.')
			dot_c--;
	i++;
	if (ft_strlen(&file[i]) != 3)
		return (ERROR);
	if (ft_strnstr(&file[i], "cub", 3) == 0)
		return (ERROR);
	return (OK);
}
