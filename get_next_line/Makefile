# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auhoris <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/26 13:39:35 by auhoris           #+#    #+#              #
#    Updated: 2021/03/15 14:11:59 by auhoris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= get_next_line.c get_next_line_utils.c

HDR	= get_next_line.h

OBJ	= $(SRCS:.c=.o)

OBJDIR	= objs/

OBJS	= $(addprefix $(OBJDIR), $(OBJ))

CFLAGS	= -Wall -Werror -Wextra -O3

RM	= rm -f

NAME	= gnl.a

$(OBJDIR)%.o: %.c $(HDR) Makefile
	mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -c $< -o $@ -I $(HDR)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re

#.SILENT: all fclean re clean $(NAME) $(OBJDIR)%.o $(OBJS)
