# NAME = cub3d

# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# CSRCS = ./src/
# LIBFT_DIR = libft/libft.a
# GET_NEXT_LINE_DIR = get_next_line.o
# MLX_DIR = /home/$(shell echo $$USER)/Downloads/minilibx-linux
# MLX_LIB = -lmlx -L$(MLX_DIR) -lXext -lX11
# SRCS =	parsing/parse_cub_file.c\
# 		parsing/read_lines.c\
# 		parsing/config_utils.c\
# 		game/init_and_setup.c\

# MSRCS = main.c 

# ALLSRCS = $(MSRCS) $(addprefix $(CSRCS), $(SRCS))

# OBJS = $(ALLSRCS:.c=.o)

# all : $(NAME)

# $(NAME): $(OBJS) $(LIBFT_DIR) $(GET_NEXT_LINE_DIR)
# 	$(CC) $(CFLAGS) $(GET_NEXT_LINE_DIR) $(OBJS) $(LIBFT_DIR) $(MLX_LIB) -o $(NAME)

# $(LIBFT_DIR):
# 	make -C libft
# $(GET_NEXT_LINE_DIR):
# 	$(CC) $(CFLAGS) get_next_line/get_next_line.c -c
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re





####################################this makefile for the mac########################################################


NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
<<<<<<< HEAD
CSRCS = ./src/
LIBFT_DIR = libft/libft.a
GET_NEXT_LINE_DIR = get_next_line.o
MLX_DIR = /home/$(shell echo $$USER)/Downloads/minilibx-linux
MLX_LIB = -lmlx -L$(MLX_DIR) -lXext -lX11
SRCS =	parsing/parse_cub_file.c\
		parsing/read_lines.c\
		parsing/config_utils.c\
		game/init_and_setup.c\
		free_data/free_all.c\
		free_data/ft_malloc.c\
=======
>>>>>>> cb24e812958f064ad681b3926b5801188e5f3bd9

# Directories
SRC_DIR = src
MLX_DIR = /Users/macbook/Downloads/minilibx
LIBFT_DIR = libft
GNL_DIR = get_next_line

# Libraries
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Source files
SRCS = \
	$(SRC_DIR)/parsing/parse_cub_file.c \
	$(SRC_DIR)/parsing/read_lines.c \
	$(SRC_DIR)/parsing/config_utils.c \
	$(SRC_DIR)/game/init_and_setup.c \
	main.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build rules
all: $(NAME)

<<<<<<< HEAD
$(LIBFT_DIR):
	make -C libft bonus
$(GET_NEXT_LINE_DIR):
	$(CC) $(CFLAGS) get_next_line/get_next_line.c -c
=======
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

# Compile libft
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Object compilation rule
>>>>>>> cb24e812958f064ad681b3926b5801188e5f3bd9
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
