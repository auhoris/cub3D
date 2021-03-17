/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:06:18 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/17 15:48:19 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define ERROR -1
# define OK 0
# define VALID_MAP_SYMB " 012NESW"
# define MAIN_ARGC 8
# define SCALE 8
# define BMP_HEADER 14
# define BMP_INFO_H 40
# define DIGITS "0123456789"
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define ESC_KEY 53
# define TURN_LEFT_KEY 123
# define TURN_RIGHT_KEY 124
# define DIV 0.3
# define MULT 1 / DIV
# define PI 3.14159265359
# define PI_2 1.57079633679
# define PI3_2 4.71238898038
# define TWO_PI 6.28318530718
# define FOV PI / 3

typedef struct	s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addres;
	int		bbp;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}				t_win;

typedef struct	s_text
{
	float	ty;
	float	tx;
	float	ty_off;
	float	ty_step;
	int		clr;
}				t_text;

typedef struct	s_sprite
{
	float	x;
	float	y;
	float	dist;
	float	s_h;
	float	s_w;
	float	s_x;
	float	s_y;
	float	s_off;
	float	s_step;
}				t_sprite;

/*
**	Структура точки
*/
typedef struct	s_floatp
{
	float	x;
	float	y;
}				t_floatp;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

/*
**	Структура конфига
*/
typedef struct	s_args
{
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	char	*sprite;
	int		res_x;
	int		res_y;
	int		floor_c;
	int		ceil_c;
}				t_args;

typedef struct	s_player
{
	float	x;
	float	y;
	float	init_x;
	float	init_y;
	float	dir;
}				t_player;

typedef struct	s_config
{
	int			d_f;
	t_win		*wall[5];
	t_sprite	*spr;
	float		d;
	int			max_l;
	int			save;
	int			screen_width;
	int			screen_height;
	float		ra;
	float		*z_buffer;
	int			sprites;
	int			size;
	int			hit;
	t_args		*args;
	t_player	*player;
	t_win		*win;
	char		**map;
	int			map_w;
	int			map_h;
	char		**content;
	t_floatp	inter;

}				t_cub;

void			start(t_cub *all, char *argv);
int				take_content(t_cub *all, int fd);
int				parsing_parameters(t_cub *all);
int				parse_ceil_floor(t_cub *all, char id);
int				parse_resol(t_cub *all, char **split);
int				parse_map(t_cub *all);
int				make_map(t_cub *all, char **map);
void			make_bmp(t_cub *all);
int				check_file(char *file);
void			start_parsing(char *file, t_cub *config);
int				set_playerpos(t_cub *config);
void			start_drawing(t_cub *config);
int				mouse(t_cub *all);
int				moving(int keycode, t_cub *config);
void			precalc_drawing(t_cub *all, t_win *wall[]);
t_floatp		horizontal_hit(t_cub *all, t_floatp fp, float pl_a);
t_floatp		vertical_hit(t_cub *all, t_floatp fp, float pl_a);
void			print_error(t_cub *all);
void			draw_wall(t_cub *all, t_win *img, float height, int x);
void			draw_ceil_floor(t_cub *all, float start, float end, int x);
void			prep_sprites(t_cub *all);
void			minimap(t_cub *all);
void			init_all(t_cub *all);
void			init_params(t_args *params);
void			init_player(t_player *player);
int				first_one(char *str);
void			quicksort(t_sprite *arr, int low, int high);
int				set_width(t_cub *all);
int				ulb(t_cub *all, int x, int flag);
int				rbd(t_cub *all, int y, int flag);
int				make_color(char *line);
void			ft_clear(char ***array);
float			kostil(float a_x, float a_y, t_floatp pl);
t_win			*make_image(t_cub *all, char *file);
float			fix_angle(float pl_a, float lower, float upper);
char			**set_array_to_null(int size);
void			pixel_put(t_win *win, int x, int y, int color);
int				get_color(t_win *data, int x, int y);
int				create_trgb(int t, int r, int g, int b);
int				in_set(char *set, char c);
int				array_lenght(char **array);
int				array_digits(char **array);
void			free_split(char **split);
void			ft_free(void *ptr);
void			ft_exit(char *str);
void			mlx_check_destroy(void *mlx, void *ptr);
void			free_check(void *ptr);
void			exit_clean(t_cub *all);
float			reverse_sqroot(float number);

#endif
