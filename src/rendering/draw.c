/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/10 19:55:48 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void put_pixel(t_cub *cub, int x, int y, int color)
{
    t_game *game;

    game = cub->game;
    if (x < 0 || y < 0 || x >= game->width * TILE || y >= game->height * TILE)
        return;
    char *ptr_img = game->img_data + ((y * game->size_line) + (x * (game->bpp / 8)));
    *(unsigned int *)ptr_img = color;
}

void    draw_player(t_cub *cub, double x, double y, int color)
{
    int i;
    int j;
    int step;
    
    i = 0;
    while (i < 12)
    {
        j = 0;
        while(j < 12)
        {
            put_pixel(cub, x + i, y + j, color);
            j++;
        }
        i++;
    }
    step = 0;
    while (step < 20)
    {
        put_pixel(cub, x + 6 + (cos(cub->player.player_angle) * step), y + 6 + (sin(cub->player.player_angle)  * step), 0xFF0000);
        step++;
    }
}

void draw_sq(t_cub *cub, int x, int y,int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE)
	{
		j = 0;
		while(j < TILE)
		{
			put_pixel(cub, x * TILE + i, y * TILE + j, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_cub *cub, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        put_pixel(cub, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
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
	if (cub->game->face_up_down == DOWN)
		y_inter += TILE;
	x_inter = cub->player.x + (y_inter - cub->player.y) / tan(cub->player.ray_angle);
	if (cub->game->face_up_down == DOWN)
		y_step = TILE;
	else
		y_step = -TILE;
	x_step = y_step /  tan(cub->player.ray_angle);
	if (cub->game->face_right_left == LEFT && x_step > 0)
		x_step *= -1;
	if (cub->game->face_right_left == RIGHT && x_step < 0)
		x_step *= -1;
	x = x_inter;
	y = y_inter;
	while (1)
	{
		if (cub->game->face_up_down == UP)
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

void    vertical(t_cub *cub)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;
    
    x_inter = floor(cub->player.x / TILE) * TILE;
	if(cub->game->face_right_left == RIGHT)
        x_inter += TILE;
    y_inter = cub->player.y + (tan(cub->player.ray_angle) * (x_inter - cub->player.x));
    x_step = TILE;
    if (cub->game->face_right_left == LEFT)
        x_step = -TILE;
    y_step = tan(cub->player.ray_angle) * x_step;
    if ((cub->game->face_up_down == DOWN && y_step < 0) || (cub->game->face_up_down == UP && y_step > 0))
        y_step = -y_step;
    while (is_walkable(cub, x_inter + (cub->game->face_right_left == LEFT ? -0.01 : 0.01), y_inter))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    cub->player.wall_vr_inter_y = y_inter;
    cub->player.wall_vr_inter_x = x_inter;
}

float calc_dist(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    ray_casting(t_cub *cub);
// void draw_map(t_cub *cub)
// {
//     int x;
//     double d_prj_plane;
//     double haight_wall;
    
//     while (x < (cub->game->width * TILE))
//     {
//         d_prj_plane = (cub->game->width / 2.0) / tan(FOV / 2.0);
//         haight_wall = (TILE / cub->player.res_dist) * d_prj_plane;
        
//         x++;
//     }
//     // ray_casting(cub); 
//     draw_player(cub, cub->player.x, cub->player.y, 0x00FF00);
// }

void   find_distance(t_cub *cub)
{
	double dist_h;
	double dist_v;

	dist_h = calc_dist(cub->player.x, cub->player.y, cub->player.wall_hz_inter_x, cub->player.wall_hz_inter_y);
	dist_v = calc_dist(cub->player.x, cub->player.y, cub->player.wall_vr_inter_x, cub->player.wall_vr_inter_y);
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

void    check_dir(t_cub *cub)
{
    double angle;
    
    angle = cub->player.ray_angle;
    if (angle > M_PI && angle < 2 * M_PI)
        cub->game->face_up_down = UP;
    else
        cub->game->face_up_down = DOWN;
    if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
        cub->game->face_right_left = LEFT;
    else
        cub->game->face_right_left = RIGHT;
}
void draw_texture(t_cub *cub, int ray_id, int wall_top, int wall_bottom)
{
    double tex_x;
    int  y;
    double tex_y;
    int window_height;
    float wallx;
    t_texture texture;
    int color;

    y = wall_top;
    window_height = cub->game->height * TILE;
    if (cub->player.is_hr && cub->game->face_up_down == UP)
        texture = cub->texture[0];
    else if (cub->player.is_hr && cub->game->face_up_down == DOWN)
        texture = cub->texture[1];
    else if (!cub->player.is_hr && cub->game->face_right_left == LEFT)
        texture = cub->texture[2];
    else if (!cub->player.is_hr && cub->game->face_right_left == RIGHT)
        texture = cub->texture[3];
    if (cub->player.is_hr)
        wallx = cub->player.wall_hz_inter_x - floor(cub->player.wall_hz_inter_x);
    else
        wallx = cub->player.wall_hz_inter_y - floor(cub->player.wall_hz_inter_y);
    tex_x = floor(wallx * texture.width);
    while (y < wall_bottom && y < window_height)
    {
        tex_y = (int)((y - wall_top) * texture.height / cub->game->wall_height);
        // printf("t_y = %f\n", tex_y);
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= texture.height) tex_y = texture.height - 1;
      color = *(int *)(texture.img_add + (int)((tex_y * texture.size_line + tex_x * (texture.bpp / 8))));
        put_pixel(cub, ray_id, y, color);
        y++;
    }
}
void draw_wall_line(t_cub *cub, int ray_id, int color)
{
    // int wall_height;
    int wall_top;
    int wall_bottom;
    double proj_plane_dist;
    int window_height;
    int window_width;
    // double dist_ray;
    int y;

    cub->player.res_dist = cos(cub->player.ray_angle - cub->player.player_angle) * cub->player.res_dist;
    window_height = cub->game->height * TILE;
    window_width = cub->game->width * TILE;
    proj_plane_dist = (window_width / 2.0) / tan(FOV / 2.0);
    cub->game->wall_height = (int)((TILE / cub->player.res_dist) * proj_plane_dist);
    wall_top = (window_height / 2) - (cub->game->wall_height / 2);
    wall_bottom = (window_height / 2) + (cub->game->wall_height / 2);
    // i should put it in function 
    double shade = 1.0 - (cub->player.res_dist / 1500.0);
    if (cub->player.is_hr)
        shade *= 0.5;    
    unsigned char g = ((color >> 8) & 0xFF) * shade;
    unsigned char b = (color & 0xFF) * shade;
    unsigned char r = ((color >> 16) & 0xFF) * shade;

color = (r << 16) | (g << 8) | b;

    y = 0;
    if (wall_top < 0 || wall_bottom < 0)
        wall_top = 0;
    if (wall_bottom > window_height || wall_bottom < 0)
        wall_bottom = window_height;
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
    
    while (y < window_height)
    {
        put_pixel(cub, ray_id, y, cub->config.floor_color);
        y++;
    }
}

void clear_image(t_cub *cub)
{
    int i;
    int total_pixels;
    
    total_pixels = (cub->game->width * TILE) * (cub->game->height * TILE);
    i = 0;
    while (i < total_pixels)
    {
        *((unsigned int *)cub->game->img_data + i) = 0x000000;
        i++;
    }
}

void    ray_casting(t_cub *cub)
{
    int ray_count;
	int window_width;

    // clear_image(cub);
    ray_count = 0;
	window_width = cub->game->width * TILE;
	cub->player.ray_angle = cub->player.player_angle - (FOV / 2);
	cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
	cub->player.angle_step = FOV / window_width;
	
	while (ray_count < window_width)
	{
        check_dir(cub);
		horizontal(cub);
		vertical(cub);
		find_distance(cub);
        draw_wall_line(cub, ray_count, 0xFFFF00);
		cub->player.ray_angle += cub->player.angle_step;
		cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
		ray_count++;
	}
    mlx_put_image_to_window(cub->game->mlx, cub->game->win, cub->game->img, 0, 0);
}
