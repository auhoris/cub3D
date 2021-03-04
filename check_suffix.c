/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_suffix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:59:36 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/03 16:59:38 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *file)
{
	int	i;

	i = -1;
	while (file[++i] != '.')
		;
	i++;
	if (ft_strlen(&file[i]) != 3)
		return (ERROR);
	if (ft_strnstr(&file[i], "cub", 3) == 0)
		return (ERROR);
	return (OK);
}
