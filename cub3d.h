#ifndef CUB3D_H
#define CUB3D_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
#include "/home/mfahmi/Downloads/minilibx-linux/mlx.h"
// #include "/home/mowardan/Downloads/minilibx-linux/mlx.h"
// #include "/Users/macbook/Downloads/minilibx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
# define SQUARE 32
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

typedef struct s_game t_game;

typedef struct s_config {
    char *no_texture; //  TODO fill this and check if it is NULL or not
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
    char position_player;
} t_config;

typedef struct s_player {
    double  x;
    double  y;
    char    direction;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    double  move_speed;
    double  rot_speed;
} t_player;

typedef struct s_cub {
    t_config    config;
    int         nm_line;
    char        **all_map;
    char        **map;
    int         index_a_map;
    int         first_index_map;
    t_player        player;
    t_game      *game;
} t_cub;

typedef struct s_game{
    void    *mlx;
    void    *win;
    int     width;
    int     height;
    void    *img;
	char     *img_data;
	int     bpp;
    int     size_line;
    int     endian;
    int     keys[256];
} t_game;

// typedef struct s_lines {
//     char *content;
//     struct s_lines *next;
// }   t_lines;


int is_cub_file(char *filename);
// bool    check_rules_map(char **line, t_cub *cub);
int parse_cub_file(char *filename, t_cub *cub);
// void read_lines(int fd, t_cub *cub);
bool   check_rules_map (char **line, t_cub *cub);
void mlx_init_and_setup(t_cub *cub);
void    init_mlx_fun(t_cub *cub);
int is_cub_file(char *filename);
// void mlx_init_and_setup(t_cub *cub);
// void    ft_free_all(t_list **head);
void    init_player(t_cub *cub);
// void    move_player(t_cub *cub, double move_x, double move_y);
void    ft_free_all();
void	check_element(t_cub *cub);
void	read_lines(int fd, t_cub *cub, char *filename);
void    free_mlx_data(t_cub *cub);
void    draw_map(t_cub *cub);
void    init_player(t_cub *cub);
int     handle_key(int keycode, t_cub *cub);
void    move_forward(t_cub *cub);
void    move_backward(t_cub *cub);



#endif