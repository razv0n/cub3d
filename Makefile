NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
CSRCS = ./src/
LIBFT_DIR = libft/libft.a
GET_NEXT_LINE_DIR = get_next_line.o
MLX_DIR = /home/$(shell echo $$USER)/Downloads/minilibx-linux
MLX_LIB = -lmlx -L$(MLX_DIR) -lXext -lX11
SRCS =	parsing/parse_cub_file.c\
		parsing/read_lines.c\
		parsing/config_utils.c\
		game/init_and_setup.c\

MSRCS = main.c 

ALLSRCS = $(MSRCS) $(addprefix $(CSRCS), $(SRCS))

OBJS = $(ALLSRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR) $(GET_NEXT_LINE_DIR)
	$(CC) $(CFLAGS) $(GET_NEXT_LINE_DIR) $(OBJS) $(LIBFT_DIR) $(MLX_LIB) -o $(NAME)

$(LIBFT_DIR):
	make -C libft
$(GET_NEXT_LINE_DIR):
	$(CC) $(CFLAGS) get_next_line/get_next_line.c -c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
