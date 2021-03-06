# Bin
name			= cub3D

# Directories
srcdir			= srcs
objdir			= objs
libdir			= libs
incdir			= includes
gnldir			= $(libdir)/get_next_line
libftdir		= $(libdir)/libft
mlxdir			= $(libdir)/mlx

# Files
sources			= $(wildcard $(srcdir)/*.c)
inclds			= $(wildcard $(incdir)/*.h)
objects			= $(sources:$(srcdir)/%.c=$(objdir)/%.o)

# Flags and linkers
cc				= gcc
cflags			= -Wall -Werror -Wextra
mlxflags		= -framework OpenGL -framework AppKit
dbgf			= -g
sanitize		= -fsanitize=address

# Additional libraries
libft_a			= libft.a
gnl_a			= gnl.a
mlx_a			= libmlx.a
libs			= $(gnldir)/$(gnl_a) $(libftdir)/$(libft_a) $(mlxdir)/$(mlx_a)

# Utils
rm				= rm -rf



all:			 mlx lib gnl $(name)

gnl:
				@make -C $(gnldir)
lib:
				@make -C $(libftdir)
mlx:
				@make -C $(mlxdir)


$(name):		$(objects) $(libs)
				$(cc) $(cflags) $^ $(mlxflags) -o $@
				@echo "\033[0;32m"$@" compiled"

$(objdir)/%.o	: $(srcdir)/%.c Makefile $(inclds)
				@mkdir -p $(objdir)
				$(cc) $(cflags) -c $< -o $@
				@echo "Compiled "$<" successfully!"


clean:
				@make -C $(gnldir) clean
				@make -C $(libftdir) clean
				@make -C $(mlxdir) clean
				$(rm) $(objdir)
fclean:			clean
				@make -C $(gnldir) fclean
				@make -C $(libftdir) fclean
				$(rm) $(name)
re:				fclean all


.PHONY:			clean fclean re all
.SILENT:		$(name) $(objects)
