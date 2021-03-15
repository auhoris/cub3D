/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:17:04 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 21:03:30 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include "mlx/mlx.h"
#include <malloc/_malloc.h>
#include <stdlib.h>
#include <unistd.h>

void		free_contents(t_cub *all)
{
	int	i;

	i = -1;
	if (all->map)
	{
		while (all->map[++i])
			free_check(all->map[i]);
		free_check(all->map);
	}
	i = -1;
	if (all->content)
	{
		while (all->content[++i])
			free_check(all->content[i]);
		free_check(all->content);
	}
}

static void	free_all(t_cub *all, int f)
{
	free_contents(all);
	free_check(all->args->no_text);
	free_check(all->args->so_text);
	free_check(all->args->we_text);
	free_check(all->args->ea_text);
	free_check(all->args->sprite);
	free_check(all->z_buffer);
	free_check(all->spr);
	if (f == 1)
	{
		mlx_check_destroy(all->win->mlx, all->wall[0].img);
		mlx_check_destroy(all->win->mlx, all->wall[1].img);
		mlx_check_destroy(all->win->mlx, all->wall[2].img);
		mlx_check_destroy(all->win->mlx, all->wall[3].img);
		mlx_check_destroy(all->win->mlx, all->wall[4].img);
		if (all->win)
			mlx_destroy_window(all->win->mlx, all->win->win);
		free_check(all->win->mlx);
	}
}

void		exit_clean(t_cub *all)
{
	free_all(all, 1);
	exit(0);
}

void		print_error(t_cub *all)
{
	ft_putendl_fd("Error\nInvalid argumetns", 2);
	free_all(all, 0);
	exit(1);
}
