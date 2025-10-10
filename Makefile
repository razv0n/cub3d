NAME = cub3d
CFALGS = -Wall -Wextra -Werror -g3
CC = cc
FUN = main.c 
OBJ = $(FUN:.c=.o)
LINKING = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm
all : $(NAME)

$(NAME):