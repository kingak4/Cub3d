CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3d
RM = rm -rf
AR = ar rcs

FILES = src/parsing/main.c src/parsing/file_check.c src/parsing/make_one_s.c src/parsing/pars_file.c src/parsing/is_ok.c src/parsing/checkers_p2.c src/parsing/read_map.c src/parsing/is_player.c src/parsing/check_texture.c src/parsing/wall_check.c src/parsing/w2.c src/parsing/final.c
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
