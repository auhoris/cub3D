/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:17:04 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/09 14:10:29 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

void	free_all(t_config *all)
{
	int	i;

	if (all->content != NULL)
	{
		i = -1;
		while (all->content[++i])
			ft_free(all->content[i]);
		ft_free(all->content);
	}
	if (all->map != NULL)
	{
		i = -1;
		while (all->map[++i])
			ft_free(all->map[i]);
		ft_free(all->map);
	}
}

void	print_error(t_config *all, int e_code)
{
	ft_putendl_fd("Error\nInvalid argumetns", 2);
	free_all(all);
	exit(1);
}
