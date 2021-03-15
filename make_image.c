/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/15 20:13:53 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

t_win	make_image(t_cub *all, char *file)
{
	t_win	win;

	if ((win.img = mlx_xpm_file_to_image(all->win->mlx,
					file, &win.img_width, &win.img_height)) == NULL)
		print_error(all);
	win.addres = mlx_get_data_addr(win.img,
			&win.bbp, &win.line_length, &win.endian);
	return (win);
}
