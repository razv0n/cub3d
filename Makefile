NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
CSRCS = ./src/
MLX_DIR = /home/mowardan/Downloads/minilibx-linux
MLX_LIB = -lmlx -L$(MLX_DIR) -lXext -lX11
SRCS =	parsing/parse_cub_file.c\
		parsing/read_lines.c\
		parsing/config_utils.c\
		game/init_and_setup.c\

MSRCS = main.c 

ALLSRCS = $(MSRCS) $(addprefix $(CSRCS), $(SRCS))

OBJS = $(ALLSRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
