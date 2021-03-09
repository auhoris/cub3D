/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation_structs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 23:17:42 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/09 20:49:55 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx/mlx.h"
#include <stdio.h>

void	init_params(t_args *args)
{
	args->no_text = NULL;
	args->so_text = NULL;
	args->we_text = NULL;
	args->ea_text = NULL;
	args->sprite = NULL;
	args->res_x = -1;
	args->res_y = -1;
	args->ceil_c = -1;
	args->floor_c = -1;
}

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
}

void	init_all(t_config *all)
{
	all->spr = NULL;
	all->d = 0;
	all->max_l = 0;
	all->save = 0;
	all->map = NULL;
	all->map_h = 0;
	all->map_w = 0;
	all->size = 0;
	all->content = NULL;
	all->inter.x = 0;
	all->inter.y = 0;
	all->sprites = 0;
	all->z_buffer = NULL;
	mlx_get_screen_size(&all->screen_width, &all->screen_height);
}
