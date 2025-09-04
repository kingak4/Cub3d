CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3d
RM = rm -rf
AR = ar rcs

FILES = src/main.c src/hooks.c src/raycasts.c src/utils.c src/rotate_and_move.c src/wall_renderer.c main.c file_check.c make_one_s.c pars_file.c is_ok.c checkers_p2.c read_map.c is_player.c
OBJS = $(FILES:.c=.o) 

LIBFT_PATH = libft
LIBFTNAME = $(LIBFT_PATH)/libft.a

MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm
INCLUDES = -Imlx -I/usr/include -I$(LIBFT_PATH)/includes

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	make -C mlx
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFTNAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	make clean -C mlx
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	make clean -C mlx
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
