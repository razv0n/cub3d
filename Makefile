NAME		= cub3d
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g3

SRC_DIR	= src
LIB_DIR	= libs
LIBFT_DIR	= $(LIB_DIR)/libft
LIBFT		= $(LIBFT_DIR)/libft.a
GNL_DIR	= $(LIB_DIR)/get_next_line
GNL_SRC	= $(GNL_DIR)/get_next_line.c
GNL_OBJ	= $(GNL_DIR)/get_next_line.o

MLX_DIR	= /home/$(shell echo $$USER)/Downloads/minilibx-linux
MLX_LIB	= -lmlx -L$(MLX_DIR) -lXext -lX11 -lm

SRC_FILES		= main.c \
			core/init_and_setup.c \
			game/events.c \
			game/player.c \
			parsing/parse_color.c \
			memory/free_all.c \
			memory/ft_malloc.c \
			parsing/config_utils.c \
			parsing/parse_config_and_map.c \
			parsing/parse_cub_file.c \
			parsing/read_lines.c \
			rendering/draw.c \
			rendering/raycasting.c \
			rendering/help_rendering.c \
			game/move_rotation_player.c \

SRCS		= $(addprefix $(SRC_DIR)/,$(SRC_FILES))
OBJS		= $(SRCS:.c=.o)
INCLUDES	= -I include -I $(LIBFT_DIR) -I $(GNL_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJ) $(LIBFT) $(MLX_LIB) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) bonus

$(GNL_OBJ): $(GNL_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus