/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:23:10 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/17 18:33:04 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libs/get_next_line/get_next_line.h"
# include "./libs/libft/libft.h"
// # include "/home/mfahmi/Downloads/minilibx-linux/mlx.h"
# include "/home/mowardan/Downloads/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE 32
# define KEY_W 119
# define KEY_A 100
# define KEY_S 115
# define KEY_D 97
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef enum s_direction
{
	DOWN,
	UP,
	LEFT,
	RIGHT,
}				t_direction;

typedef enum s_msg
{
	wall,
	color,
	empty,
	nothing,
	element,
	mlx,
}				t_msg;

typedef struct s_config
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	char		position_player;
}				t_config;

typedef struct s_texture
{
	void		*img;
	char		*img_add;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		player_angle;
	double		ray_angle;
	double		angle_step;
	char		direction;
	double		dir_x;
	double		wall_hz_inter_x;
	double		wall_hz_inter_y;
	double		wall_vr_inter_x;
	double		wall_vr_inter_y;
	double		res_dist;
	double		dir_y;
	double		plane_x;
	bool		is_hr;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	double		dist;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	void		*img;
	char		*img_data;
	int			bpp;
	t_direction	face_up_down;
	t_direction	face_right_left;
	int			size_line;
	int			wall_height;
	int			endian;
	double		width_t;
	double		height_t;
	double		step_x;
	double		step_y;
	double		inter_x;
	double		inter_y;
	double		proj_plane_dist;
	double		fov;
}				t_game;

typedef struct s_cub
{
	t_config	config;
	t_texture	texture[4];
	t_msg		mesaage;
	int			nm_line;
	char		**map;
	char		**map_prsv;
	int			length_map;
	int			*rows;
	int			index_map;
	t_player	player;
	t_game		game;
}				t_cub;


int				is_cub_file(char *filename);
bool			parse_cub_file(char *filename, t_cub *cub);
void			check_rules_map(char **line, t_cub *cub);
void			mlx_init_and_setup(t_cub *cub);
void			init_mlx_fun(t_cub *cub);
int				is_cub_file(char *filename);
void			init_player(t_cub *cub);
void			ft_free_all(t_msg mesaage);
void			check_element(t_cub *cub);
void			read_lines(int fd, t_cub *cub, char *filename);
void			free_mlx_data(t_cub *cub);
void			init_player(t_cub *cub);
int				handle_key(int keycode, t_cub *cub);
void			find_distance(t_cub *cub);
int				handle_close(void *param);
bool			check_rbg(char *line, t_cub *cub, char RBG);
char			*remove_char(char *line);
bool			check_the_colors(char *line, int nm_line, t_cub *cub);
bool			check_the_texture_wall(char *line, short nm_line, t_cub *cub);
void			put_pixel(t_cub *cub, int x, int y, int color);
unsigned int	get_pixel(t_texture texture, int x, int y);
void			move_forward(t_cub *cub);
void			check_dir(t_cub *cub);
bool			is_walkable(t_cub *cub, double x_p, double y_p);
void			move_backward(t_cub *cub);
double			normalize_angle(double angle);
float			calc_dist(float x1, float y1, float x2, float y2);
void			ray_casting(t_cub *cub);
void			rotate(t_cub *cub, t_direction dir);
void			move_backward(t_cub *cub);
void			set_player_direction(t_cub *cub);
void			move_forward(t_cub *cub);
void			move_left(t_cub *cub);
void			draw_wall_line(t_cub *cub, int ray_id);
void			update_player_dir(t_cub *cub);
void			move_right(t_cub *cub);
void			free_mlx_data(t_cub *cub);

#endif
