NAME = cub3d
CFALGS = -Wall -Wextra -Werror -g3
CC = cc
FUN = main.c parsing/config_utils.c parsing/map_utils.c parsing/parse_config_and_map.c parsing/parse_cub_file.c parsing/read_lines.c
OBJ = $(FUN:.c=.o)
LINKING = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm
all : $(NAME)

$(NAME): $(OBJ)
	