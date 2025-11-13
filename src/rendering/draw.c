/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/13 15:37:58 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// todo fix the player hating the wall
void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*ptr_img;

	if (x < 0 || y < 0 || x >= cub->game.width * TILE || y >= cub->game.height
		* TILE)
		return ;
	ptr_img = cub->game.img_data + ((y * cub->game.size_line) + (x
				* (cub->game.bpp / 8)));
	*(unsigned int *)ptr_img = color;
}

unsigned int	get_pixel(t_texture texture, int x, int y)
{
	char	*ptr_img;

	if (x < 0 || y < 0 || x >= texture.width || y >= texture.height)
		return (0);
	ptr_img = texture.img_add + ((y * texture.size_line) + (x * (texture.bpp
					/ 8)));
	return (*(unsigned int *)ptr_img);
}

void	draw_player(t_cub *cub, double x, double y, int color)
{
	int	i;
	int	j;
	int	step;

	i = 0;
	while (i < 12)
	{
		j = 0;
		while (j < 12)
		{
			put_pixel(cub, x + i, y + j, color);
			j++;
		}
		i++;
	}
	step = 0;
	while (step < 20)
	{
		put_pixel(cub, x + 6 + (cos(cub->player.player_angle) * step), y + 6
			+ (sin(cub->player.player_angle) * step), 0xFF0000);
		step++;
	}
}

void	draw_sq(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < TILE)
		{
			put_pixel(cub, x * TILE + i, y * TILE + j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_cub *cub, int x0, int y0, int x1, int y1, int color)
{
	int (dx), sx, dy, sy, err, e2;
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		put_pixel(cub, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	horizontal(t_cub *cub)
{
	double	y_inter;
	double	x_inter;
	double	y_step;
	double	x_step;
	double	x;
	double	y;
	double	check_y;

	y_inter = floor(cub->player.y / TILE) * TILE;
	if (cub->game.face_up_down == DOWN)
		y_inter += TILE;
	x_inter = cub->player.x + (y_inter - cub->player.y)
		/ tan(cub->player.ray_angle);
	if (cub->game.face_up_down == DOWN)
		y_step = TILE;
	else
		y_step = -TILE;
	x_step = y_step / tan(cub->player.ray_angle);
	if (cub->game.face_right_left == LEFT && x_step > 0)
		x_step *= -1;
	if (cub->game.face_right_left == RIGHT && x_step < 0)
		x_step *= -1;
	x = x_inter;
	y = y_inter;
	while (1)
	{
		if (cub->game.face_up_down == UP)
			check_y = y - 0.01;
		else
			check_y = y + 0.01;
		if (!is_walkable(cub, x, check_y))
			break ;
		x += x_step;
		y += y_step;
	}
	cub->player.wall_hz_inter_x = x;
	cub->player.wall_hz_inter_y = y;
}

void	vertical(t_cub *cub)
{
	double	x_inter;
	double	y_inter;
	double	x_step;
	double	y_step;

	x_inter = floor(cub->player.x / TILE) * TILE;
	if (cub->game.face_right_left == RIGHT)
		x_inter += TILE;
	y_inter = cub->player.y + (tan(cub->player.ray_angle) * (x_inter
				- cub->player.x));
	x_step = TILE;
	if (cub->game.face_right_left == LEFT)
		x_step = -TILE;
	y_step = tan(cub->player.ray_angle) * x_step;
	if ((cub->game.face_up_down == DOWN && y_step < 0)
		|| (cub->game.face_up_down == UP && y_step > 0))
		y_step = -y_step;
	while (is_walkable(cub, x_inter + (cub->game.face_right_left == LEFT ?
				-0.01 : 0.01), y_inter))
	{
		x_inter += x_step;
		y_inter += y_step;
	}
	cub->player.wall_vr_inter_y = y_inter;
	cub->player.wall_vr_inter_x = x_inter;
}

float	calc_dist(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void			ray_casting(t_cub *cub);
// void draw_map(t_cub *cub)
// {
//     int x;
//     double d_prj_plane;
//     double haight_wall;

//     while (x < (cub->game.width * TILE))
//     {
//         d_prj_plane = (cub->game.width / 2.0) / tan(FOV / 2.0);
//         haight_wall = (TILE / cub->player.res_dist) * d_prj_plane;

//         x++;
//     }
//     // ray_casting(cub);
//     draw_player(cub, cub->player.x, cub->player.y, 0x00FF00);
// }

void	find_distance(t_cub *cub)
{
	double	dist_h;
	double	dist_v;

	dist_h = calc_dist(cub->player.x, cub->player.y,
			cub->player.wall_hz_inter_x, cub->player.wall_hz_inter_y);
	dist_v = calc_dist(cub->player.x, cub->player.y,
			cub->player.wall_vr_inter_x, cub->player.wall_vr_inter_y);
	if (dist_h < dist_v)
	{
		cub->player.res_dist = dist_h;
		cub->player.is_hr = true;
	}
	else
	{
		cub->player.wall_hz_inter_x = cub->player.wall_vr_inter_x;
		cub->player.wall_hz_inter_y = cub->player.wall_vr_inter_y;
		cub->player.res_dist = dist_v;
		cub->player.is_hr = false;
	}
}

void	check_dir(t_cub *cub)
{
	double	angle;

	angle = cub->player.ray_angle;
	if (angle > M_PI && angle < 2 * M_PI)
		cub->game.face_up_down = UP;
	else
		cub->game.face_up_down = DOWN;
	if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
		cub->game.face_right_left = LEFT;
	else
		cub->game.face_right_left = RIGHT;
}

void	draw_texture(t_cub *cub, int ray_id, int wall_top, int wall_bottom)
{
	int			tex_x;
	int			y;
	int			tex_y;
	int			window_height;
	float		wallx;
	t_texture	texture;
	int			color;

	y = wall_top;
	window_height = cub->game.height * TILE;
	if (cub->player.is_hr && cub->game.face_up_down == UP)
		texture = cub->texture[0];
	else if (cub->player.is_hr && cub->game.face_up_down == DOWN)
		texture = cub->texture[1];
	else if (!cub->player.is_hr && cub->game.face_right_left == LEFT)
		texture = cub->texture[2];
	else if (!cub->player.is_hr && cub->game.face_right_left == RIGHT)
		texture = cub->texture[3];
	if (!cub->player.is_hr)
		wallx = cub->player.wall_hz_inter_y / TILE;
	else
		wallx = cub->player.wall_hz_inter_x / TILE;
	// ?why i calculate the wallx multilple times
	wallx -= floor(wallx);
	tex_x = (int)(wallx * texture.width);
	if ((!cub->player.is_hr && cub->game.face_right_left == RIGHT)
		|| (cub->player.is_hr && cub->game.face_up_down == UP))
		tex_x = texture.width - tex_x - 1; //  ?the math behind it
	while (y < wall_bottom)
	{
		if (y >= 0 && y < window_height)
		{
			tex_y = (int)(((y - wall_top) * (texture.height)
						/ cub->game.wall_height));
			color = get_pixel(texture, tex_x, tex_y);
			// color = *(texture.img_add + ((tex_y * texture.size_line) + (tex_x
			// * (texture.bpp / 8))));
			// printf("color: %d and the tex_y: %d\n", color, tex_y);
			put_pixel(cub, ray_id, y, color);
		}
		y++;
	}
}

void	draw_wall_line(t_cub *cub, int ray_id)
{
	int		wall_top;
	int		wall_bottom;
	double	proj_plane_dist;
	int		window_height;
	int		window_width;
	int		y;

	cub->player.res_dist = cos(cub->player.ray_angle - cub->player.player_angle)
		* cub->player.res_dist;
	window_height = cub->game.height * TILE;
	window_width = cub->game.width * TILE;
	proj_plane_dist = (window_width / 2.0) / tan(FOV / 2.0); // so the cos here
	cub->game.wall_height = (int)((TILE / cub->player.res_dist)
			* proj_plane_dist);
	wall_top = (window_height / 2) - (cub->game.wall_height / 2);
	wall_bottom = wall_top + cub->game.wall_height;
	y = 0;
	while (y < wall_top && y < window_height)
	{
		put_pixel(cub, ray_id, y, cub->config.ceiling_color);
		y++;
	}
	draw_texture(cub, ray_id, wall_top, wall_bottom);
	// y = wall_top;
	// while (y < wall_bottom && y < window_height)
	// {
	//     put_pixel(cub, ray_id, y, color);
	//     y++;
	// }
	y = wall_bottom;
	while (y < window_height)
	{
		put_pixel(cub, ray_id, y, cub->config.floor_color);
		y++;
	}
}

// void clear_image(t_cub *cub)
// {
//     int i;
//     int total_pixels;

//     total_pixels = (cub->game.width * TILE) * (cub->game.height * TILE);
//     i = 0;
//     while (i < total_pixels)
//     {
//         *((unsigned int *)cub->game.img_data + i) = 0x000000;
//         i++;
//     }
// }

void	ray_casting(t_cub *cub)
{
	int	ray_count;
	int	window_width;

	// clear_image(cub);
	// ! why i dont use the  clear function
	//? when i use the projection plane like a const it doesnt work well
	//? why i use the tan in the projection plane calculation and not the cos
	//?why the texture woorks wiht the function get_pixel but not when i access directly to the img_add
	// ? why in the dir i use the cos and sin
	// todo ray casting add the -1 and +1 in the up down or right left check
	// todo optimise the ray casting
	ray_count = 0;
	window_width = cub->game.width * TILE;
	cub->player.ray_angle = cub->player.player_angle - (FOV / 2);
	cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
	cub->player.angle_step = FOV / window_width;
	while (ray_count < window_width)
	{
		check_dir(cub);
		horizontal(cub);
		vertical(cub);
		find_distance(cub);
		draw_wall_line(cub, ray_count);
		cub->player.ray_angle += cub->player.angle_step;
		cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
		ray_count++;
	}
	mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
}
