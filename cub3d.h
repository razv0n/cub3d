#ifndef CUB3D_H
#define CUB3D_H

# include "./libft/libft.h"
# include "./w/get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_config {
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
} t_config;

typedef struct s_player {
    int x, y;
    char direction;
} t_player;

typedef struct s_cub {
    t_config config;
    char **map;
    int map_width;
    int map_height;
    t_player player;
} t_cub;

typedef struct s_lines {
    char *content;
    struct s_lines *next;
}   t_lines;


int is_cub_file(char *filename);
int parse_cub_file(char *filename, t_cub *cub);
int read_lines(int fd);

#endif