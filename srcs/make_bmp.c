/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:11:56 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/15 14:26:10 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/fcntl.h>
#include <unistd.h>

static void	put_pixels_to_file(t_cub *all, int fd)
{
	int	x;
	int	y;

	y = all->args->res_y;
	while (y-- > 0)
	{
		x = -1;
		while (++x < all->args->res_x)
			write(fd, all->win->addres +
					(y * all->win->line_length + x * (all->win->bbp / 8)), 4);
	}
}

static void	get_info_header(t_cub *all, int fd)
{
	char	bmp_infoheader[BMP_INFO_H];
	int		i;

	bmp_infoheader[0] = BMP_INFO_H;
	bmp_infoheader[1] = 0;
	bmp_infoheader[2] = 0;
	bmp_infoheader[3] = 0;
	bmp_infoheader[4] = all->args->res_x;
	bmp_infoheader[5] = all->args->res_x >> 8;
	bmp_infoheader[6] = all->args->res_x >> 16;
	bmp_infoheader[7] = all->args->res_x >> 24;
	bmp_infoheader[8] = all->args->res_y;
	bmp_infoheader[9] = all->args->res_y >> 8;
	bmp_infoheader[10] = all->args->res_y >> 16;
	bmp_infoheader[11] = all->args->res_y >> 24;
	bmp_infoheader[12] = 1;
	bmp_infoheader[13] = 0;
	bmp_infoheader[14] = 32;
	bmp_infoheader[15] = 0;
	i = 15;
	while (++i < BMP_INFO_H)
		bmp_infoheader[i] = 0;
	write(fd, bmp_infoheader, BMP_INFO_H);
}

void		make_bmp(t_cub *all)
{
	int		fd;
	char	bmp_header[BMP_HEADER];
	int		file_size;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	file_size = BMP_HEADER + BMP_INFO_H +
		all->args->res_x * all->args->res_y * 3;
	bmp_header[0] = 'B';
	bmp_header[1] = 'M';
	bmp_header[2] = file_size;
	bmp_header[3] = file_size >> 8;
	bmp_header[4] = file_size >> 16;
	bmp_header[5] = file_size >> 24;
	bmp_header[6] = 0;
	bmp_header[7] = 0;
	bmp_header[8] = 0;
	bmp_header[9] = 0;
	bmp_header[10] = BMP_HEADER + BMP_INFO_H;
	bmp_header[11] = 0;
	bmp_header[12] = 0;
	bmp_header[13] = 0;
	write(fd, bmp_header, BMP_HEADER);
	get_info_header(all, fd);
	put_pixels_to_file(all, fd);
	exit(0);
}
