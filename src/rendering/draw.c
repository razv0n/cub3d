/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/29 21:48:07 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void put_pixel(t_cub *cub, int x, int y, int color)
{
    t_game *game;

    game = cub->game;
    if (x < 0 || y < 0 || x >= game->width * SQUARE || y >= game->height * SQUARE)
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
            put_pixel(cub, (int)(x * SQUARE) + i, (int)(y * SQUARE) + j, color);
            j++;
        }
        i++;
    }
    step = 0;
    while (step < 20)
    {
        put_pixel(cub, (int)(x * SQUARE) + 6 + (int)(cub->player.dir_x * step), (int)(y * SQUARE) + 6 + (int)(cub->player.dir_y * step), 0xFF0000);
        step++;
    }
}

void draw_sq(t_cub *cub, int x, int y,int color)
{
	int i;
	int j;

	i = 0;
	while (i < SQUARE)
	{
		j = 0;
		while(j < SQUARE)
		{
			put_pixel(cub, x * SQUARE + i, y * SQUARE + j, color);
			j++;
		}
		i++;
	}
}

void draw_ray(t_cub *cub, double inter_x, double inter_y, int color)
{
	int x0 = (int)(cub->player.x * SQUARE);
	int y0 = (int)(cub->player.y * SQUARE);
	int x1;
	int y1;

	// if intersection looks like tile coordinate, convert to pixels; otherwise assume already pixels
	if (inter_x <= cub->game->width)
		x1 = (int)(inter_x * SQUARE);
	else
		x1 = (int)inter_x;
	if (inter_y <= cub->game->height)
		y1 = (int)(inter_y * SQUARE);
	else
		y1 = (int)inter_y;

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

void    horizontal(t_cub *cub)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;
    
    y_inter = ((int)(cub->player.y / SQUARE)) * SQUARE;
    x_inter =  cub->player.x + ((y_inter - cub->player.y) / tan(cub->player.ray_angle));
    x_step = SQUARE / tan(cub->player.ray_angle);
    y_step = SQUARE;
    while (is_walkable(cub, x_inter, y_inter))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    cub->player.wall_hz_inter_x = x_inter;
    cub->player.wall_hz_inter_y = y_inter;
}

void    vertical(t_cub *cub)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;
    
    x_inter = ((int)(cub->player.x / SQUARE)) * SQUARE;
    y_inter = cub->player.y + (tan(cub->player.ray_angle) * (x_inter - cub->player.x));
    x_step = SQUARE;
    y_step = tan(cub->player.ray_angle) * SQUARE;
    while (is_walkable(cub, x_inter, y_inter))
    {
        x_inter += x_step;
        y_inter += y_step;
    }
    cub->player.wall_vr_inter_y = y_inter;
    cub->player.wall_vr_inter_x = x_inter;
}

void    ray_casting(t_cub *cub);
void draw_map(t_cub *cub)
{
    int y = 0;
    
    while (cub->map[y])
    {
        int x = 0;
        while (x < cub->game->width)
        {
            if ((x >= (int)ft_strlen(cub->map[y]) && x < cub->game->width) || cub->map[y][x] == '1')
            draw_sq(cub, x, y, 0x00FFF0);
            else if (cub->map[y][x] == '0' || cub->map[y][x] == cub->config.position_player)
            draw_sq(cub, x, y , 0x000F00);
            // else
            x++;
        }
        y++;
    }
    ray_casting(cub);
    draw_player(cub, cub->player.x, cub->player.y, 0x00FF00);
}

void    ray_casting(t_cub *cub)
{
	int     i;
	// double x;
	// double y;

	cub->player.player_angle = atan2(cub->player.dir_y, cub->player.dir_x);
	cub->player.ray_angle = cub->player.player_angle - (FOV / 2);
	cub->player.angle_step = FOV / cub->game->width;

	i = 0;
	while (i < cub->game->width)
	{
		// x = cub->player.x;
		// y = cub->player.y;
		horizontal(cub);
		vertical(cub);
		if (cub->player.wall_hz_inter_x + cub->player.wall_hz_inter_y > cub->player.wall_vr_inter_x + cub->player.wall_vr_inter_y)
		{
			cub->player.wall_hz_inter_x =  cub->player.wall_vr_inter_x;
			cub->player.wall_hz_inter_y = cub->player.wall_vr_inter_y;
		}
		// if (fabs(cub->player.wall_hz_inter_x - cub->player.x) < fabs(cub->player.wall_vr_inter_x - cub->player.x))
		// {
		//     put_pixel(cub, i, 0, 0xFFFF00); // just to test horizontal intersection
		// }
		// else
		// {
		//     put_pixel(cub, i, 0, 0xFF00FF); // just to test vertical intersection
		// }
		cub->player.ray_angle += cub->player.angle_step; // add the ray angle with how many angles that we want
		i++;
	}
}