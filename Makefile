NAME = so_long
CC = cc -g 
CFLAGS = -Wall -Wextra -Werror

SOURCES = code/so_long.c code/player.c code/window_actions.c code/map.c code/checks.c code/collect.c code/start_check.c code/path.c
OBJECTS = $(SOURCES:.c=.o)

MLX_DIR = code/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm

LIBFT = code/libft/libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
