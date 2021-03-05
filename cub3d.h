/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:06:18 by auhoris           #+#    #+#             */
/*   Updated: 2021/03/05 20:40:45 by auhoris          ###   ########.fr       */
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

/*
**	BMP
*/
# define BMP_HEADER 14
# define BMP_INFO_H 40

# define DIGITS "0123456789"
/*
**	Key bindings
*/
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
# define RATIO 1

# define HEIGHT 500

typedef struct	s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addres;
	int	bbp;
	int	line_length;
	int	endian;
	int	img_width;
	int	img_height;
}		t_win;


typedef struct s_text
{
	float	ty;
	float	tx;
	float	ty_off;
	float	ty_step;
	int	clr;
}		t_text;

typedef struct s_sprite
{
	float	x;
	float	y;
	float	dist;
	t_win	img;
	float	s_h;
	float	s_w;
	float	s_x;
	float	s_y;
	float	s_off;
	float	s_step;
}		t_sprite;
/*
**	Структура точки
*/
typedef struct s_floatp
{
	float	x;
	float	y;
}		t_floatp;

typedef struct	s_point
{
	int	x;
	int	y;
}		t_point;


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
		int	res_x;
		int	res_y;
		int	floor_c;
		int	ceil_c;
}				t_args;

typedef struct	s_player
{
	float	x;
	float	y;
	float	init_x;
	float	init_y;
	float	dir;
	float	fov_start;
	float	fov_end;
}		t_player;

typedef struct	s_config
{
	float		d;
	int		max_l;
	int		save;
	int		screen_width;
	int		screen_height;
	float		ra;
	float		*z_buffer;
	int		sprites;
	int		size;
	int		hit;
	t_args	*args;
	t_player	*player;
	t_win		*win;
	char		**map;
	int		map_w;
	int		map_h;
	char		**content;
	t_floatp	inter;

}		t_config;

void	start(t_config *all, char *argv);

int	take_content(t_config *all, int fd);
int	parsing_parameters(t_config *all);
int	parse_ceil_floor(t_config *all, char **split, char id);
int	parse_resol(t_config *all, char **split);
int	parse_map(t_config *all);
int	make_map(t_config *all, char **map);
void	make_bmp(t_config *all);

int	check_file(char *file);
void	start_parsing(char *file, t_config *config);
int	set_playerpos(t_config *config);
void	start_drawing(t_config *config);
int	mouse(int keycode, t_config *all);
int	moving(int keycode, t_config *config);

/*
**	Calculus
*/
void		precalc_drawing(t_config *all, t_win wall[]);
t_floatp	horizontal_hit(t_config *all, t_floatp fp, float pl_a);
t_floatp	vertical_hit(t_config *all, t_floatp fp, float pl_a);
void		print_error(t_config *all, int e_code);

/*
**	Drawing part
*/
void	draw_wall(t_config *all, t_win *img, float height, int x);
void	draw_ceil_floor(t_config *all, float start, float end, int x);
void	prep_sprites(t_config *all);

/*
**	Minimap
*/
void	minimap(t_config *all);

void	init_all(t_config *all);
void	init_params(t_args *params);
void	init_player(t_player *player);

/*
**	UTILS
*/
int	set_width(t_config *all);
int	ulb(t_config *all, int x, int flag);
int	rbd(t_config *all, int y, int flag);
int	make_color(t_config *all, char *line);
void	ft_clear(char ***array);
float	kostil(float a_x, float a_y, t_floatp pl);
t_win	make_image(t_config *all, char *file);
float	fix_angle(float pl_a, float lower, float upper);
char		**set_array_to_null(int size);
void	pixel_put(t_win *win, int x, int y, int color);
int	get_color(t_win *data, int x, int y);
int	create_trgb(int t, int r, int g, int b);
int	in_set(char *set, char c);

void	cout_all(t_config *all);
void	cout_splitted(char **split);

int	array_lenght(char **array);
int	array_digits(char **array);

void	free_split(char **split);
void	ft_free(void *ptr);
void	ft_exit(char *str);

float	reverse_sqroot(float number);
#endif
