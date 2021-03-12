# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auhoris <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/23 18:13:38 by auhoris           #+#    #+#              #
#    Updated: 2021/03/12 17:04:09 by auhoris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D


SRCS		= main.c take_content.c parsing_parameters.c \
		  parse_floor_ceil.c check_suffix.c \
		  checking_config.c utils_pt1.c initiation_structs.c \
		  utils_pt2.c set_player.c moving_bonus.c \
		  drawing.c ft_free.c parse_resol_sprite.c \
		  print_error.c parse_map.c make_image.c \
		  sprites.c hits.c mouse.c \
		  utils_pt3.c make_map.c make_bmp.c \
		  start.c precalc_drawing.c map_utils.c \
		  quicksort.c


#BONUS_S		= movin_bonus.c


OBJ		= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJRID), $(OBJ))


CFLAGS		= -Wall -Werror -Wextra
#CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
MLX_FLAGS	= -framework OpenGL -framework AppKit
OPTFLAGS	= -O3
LEAKFLAGS	= -ggdb3 -std=c11


MLX_A		= libmlx.a
LIBFT_A		= libft.a
GNL_A		= gnl.a


LIBFTD		= libft/
MLXD		= mlx/
GNLD		= get_next_line/
OBJRID		= objs/

CUB_H		= cub3d.h
LIBS		= $(GNLD)$(GNL_A) $(MLXD)$(MLX_A) $(LIBFTD)$(LIBFT_A)

all:	$(NAME)

$(NAME): $(OBJS) $(CUB_H)
	@make -C $(MLXD)
	@make -C $(LIBFTD)
	@make -C $(GNLD)
	gcc $(CFLAGS) $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)


$(OBJRID)%.o: %.c $(CUB_H)
	@mkdir -p $(OBJRID)
	gcc $(OPTFLAGS) -MMD -c $< -o $@

clean:
	@rm -rf $(OBJRID)
	@make -C $(GNLD) clean
	@make -C $(MLXD) clean
	@make -C $(LIBFTD) clean

fclean:	clean
	rm -f $(NAME)
	@make -C $(LIBFTD) fclean
	@make -C $(GNLD) fclean

norm:
	norminette *.c $(LIBFTD)*.c $(GNLD)*.c
re:	fclean all

.PHONY:	fclean all re clean

.SILENT: fclean clean all re $(NAME) $(OBJS) $(OBJRID)
