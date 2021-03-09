/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/09 20:54:48 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

t_win	make_image(t_config *all, char *file)
{
	t_win	win;

	if ((win.img = mlx_xpm_file_to_image(all->win->mlx,
					file, &win.img_width, &win.img_height)) == NULL)
	{
		ft_putendl_fd("Error\nInvalid arguments", 2);
		exit(1);
	}
	win.addres = mlx_get_data_addr(win.img,
			&win.bbp, &win.line_length, &win.endian);
	return (win);
}
