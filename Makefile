NAME	= libcub.a

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

SOURCES = 	main.c other/util.c other/color.c other/hook.c other/init.c \
			parse/parser.c gnl/get_next_line.c gnl/get_next_line_utils.c \
			other/error.c parse/parse_tex.c parse/parse_map.c \
			parse/parse_color.c sprites/sprites.c parse/valid_map.c \
			other/position.c sprites/spr_util.c other/hook_move.c save.c \
			parse/parse_util.c

OBJECT	= ${SOURCES:.c=.o}

HEADER	= cub3d.h ${I_MLX} ${I_GNL}

I_MLX	= -Imlx/mlx.h

I_GNL	= -Ignl/get_next_line.h

$(NAME): $(OBJECT)
	make bonus -C libft/
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)

	${CC} ${CFLAGS} -L. -lcub -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o cub3D

all:	$(NAME)

%.o:%.c		cub3d.h gnl/get_next_line.h
			${CC} ${CFLAGS} -I ${HEADER} -c $< -o $@

.PhONY: all clean fclean re

clean:
	make clean -C libft/
	-rm -f ${OBJECT}

fclean: clean
	make fclean -C libft/
	-rm -f ${NAME}
	-rm -f cub3D
	-rm -f save.bmp

re:	fclean all
