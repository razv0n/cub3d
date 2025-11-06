/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/06 11:51:10 by mfahmi           ###   ########.fr       */
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

void    horizontal(t_cub *cub)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;
    double  op;
    
    y_inter = floor(cub->player.y / TILE) * TILE;
    op = 1;
	if(cub->game->face_up_down == DOWN)
    {
        y_inter += TILE;
        op = -1;
    }
    op *= y_inter - cub->player.y;
    x_inter =  cub->player.x + (op / tan(cub->player.ray_angle));
    y_step = TILE;
    if (cub->game->face_up_down == UP)
        y_step = -TILE;
    x_step = y_step / tan(cub->player.ray_angle);
    if ((cub->game->face_right_left == RIGHT && x_step < 0) || (cub->game->face_right_left == LEFT && x_step > 0))
        x_step = -x_step;
    
    // DEBUG: Initial intersection
    printf("  H-RAY: start=(%.2f, %.2f) step=(%.2f, %.2f)\n", 
           x_inter, y_inter, x_step, y_step);
    
    int steps = 0;
    while (is_walkable(cub, x_inter, y_inter + (cub->game->face_up_down == UP ? -0.1 : 0.1)))
    {
        x_inter += x_step;
        y_inter += y_step;
        steps++;
        
        // DEBUG: Show every step
        if (steps <= 3) // Only first 3 steps to avoid spam
            printf("    H-step %d: (%.2f, %.2f) grid=(%d,%d)\n", 
                   steps, x_inter, y_inter, 
                   (int)(x_inter/TILE), (int)(y_inter/TILE));
    }
    printf("  H-HIT: (%.2f, %.2f) after %d steps\n", x_inter, y_inter, steps);
    
    cub->player.wall_hz_inter_x = x_inter;
    cub->player.wall_hz_inter_y = y_inter;
}

void draw_line(t_cub *cub, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy; // error value e_xy /

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

void    vertical(t_cub *cub)
{
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;
    double  ag;

    ag = 1;
    x_inter = floor(cub->player.x / TILE) * TILE;
	if(cub->game->face_right_left == RIGHT)
    {
        x_inter += TILE;
        ag *= -1;
    }
    ag = x_inter - cub->player.x;
    y_inter = cub->player.y + (tan(cub->player.ray_angle) * ag);
    x_step = TILE;
    if (cub->game->face_right_left == LEFT)
        x_step = -TILE;
    y_step = tan(cub->player.ray_angle) * x_step;
    if ((cub->game->face_up_down == DOWN && y_step < 0) || (cub->game->face_up_down == UP && y_step > 0))
        y_step = -y_step;
    
    // DEBUG: Initial intersection
    printf("  V-RAY: start=(%.2f, %.2f) step=(%.2f, %.2f)\n", 
           x_inter, y_inter, x_step, y_step);
    
    int steps = 0;
    while (is_walkable(cub, x_inter + (cub->game->face_right_left == LEFT ? -0.1 : 0.1), y_inter))
    {
        x_inter += x_step;
        y_inter += y_step;
        steps++;
        
        // DEBUG: Show every step
        if (steps <= 3) // Only first 3 steps
            printf("    V-step %d: (%.2f, %.2f) grid=(%d,%d)\n", 
                   steps, x_inter, y_inter, 
                   (int)(x_inter/TILE), (int)(y_inter/TILE));
    }
    printf("  V-HIT: (%.2f, %.2f) after %d steps\n", x_inter, y_inter, steps);
    
    cub->player.wall_vr_inter_y = y_inter;
    cub->player.wall_vr_inter_x = x_inter;
}

float calc_dist(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void    ray_casting(t_cub *cub);
void draw_map(t_cub *cub)
{
    int y = 0;
    
    // Uncomment to debug once at startup:
    static int debug_once = 0;
    if (!debug_once)
    {
        debug_full_game(cub);
        debug_once = 1;
    }
    
    while (cub->map[y])
    {
        int x = 0;
        while (x < cub->game->width)
        {
            if ((x >= (int)ft_strlen(cub->map[y]) && x < cub->game->width) || cub->map[y][x] == '1')
            	draw_sq(cub, x, y, 0x00FFF0);
            else if (cub->map[y][x] == '0' || cub->map[y][x] == cub->config.position_player)
            	draw_sq(cub, x, y , 0x000F00);
            x++;
        }
        y++;
    }
    ray_casting(cub);
    draw_player(cub, cub->player.x, cub->player.y, 0x00FF00);
}

void   find_distance(t_cub *cub)
{
	double dist_h;
	double dist_v;

	dist_h = calc_dist(cub->player.x, cub->player.y, cub->player.wall_hz_inter_x, cub->player.wall_hz_inter_y);
	dist_v = calc_dist(cub->player.x, cub->player.y, cub->player.wall_vr_inter_x, cub->player.wall_vr_inter_y);
	if (dist_h < dist_v)
		cub->player.res_dist = dist_h;
	else
    {
        cub->player.wall_hz_inter_x = cub->player.wall_vr_inter_x;
        cub->player.wall_hz_inter_y = cub->player.wall_vr_inter_y;
		cub->player.res_dist = dist_v;
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
    if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
        cub->game->face_right_left = LEFT;
    else
        cub->game->face_right_left = RIGHT;
}

void    ray_casting(t_cub *cub)
{
	int ray_count = 0;
	int window_width;
	double end_angle;
	
	window_width = cub->game->width * TILE;
	
	printf("\n=== RAY CASTING START ===\n");
	printf("Player Position: (%.2f, %.2f) Grid: (%d, %d)\n", 
	       cub->player.x, cub->player.y,
	       (int)(cub->player.x / TILE), (int)(cub->player.y / TILE));
	printf("Player Angle: %.4f (%.2f°)\n", cub->player.player_angle, cub->player.player_angle * 180.0 / M_PI);
	
	cub->player.ray_angle = cub->player.player_angle - (FOV / 2);
	cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
	cub->player.angle_step = FOV / window_width;
	end_angle = cub->player.player_angle + (FOV / 2);
	
	while (ray_count < window_width)
    check_dir(cub);
	{
        if (ray_count < 3)
        {
            printf("\n=== RAY #%d ===\n", ray_count);
            printf("Angle: %.4f (%.2f°) | Dir: %s %s\n", 
                   cub->player.ray_angle, cub->player.ray_angle * 180.0 / M_PI,
                   cub->game->face_up_down == UP ? "UP" : "DOWN",
                   cub->game->face_right_left == RIGHT ? "RIGHT" : "LEFT");
        }
        
		horizontal(cub);
		vertical(cub);
		find_distance(cub);
        
        if (ray_count % 32 == 0)
            draw_line(cub, cub->player.x + 6, cub->player.y + 6, 
                     cub->player.wall_hz_inter_x, cub->player.wall_hz_inter_y, 0xFFFF00);
		
        if (ray_count < 3)
        {
            printf("  FINAL: Distance=%.2f to (%.2f, %.2f)\n", 
                   cub->player.res_dist, 
                   cub->player.wall_hz_inter_x, 
                   cub->player.wall_hz_inter_y);
        }
        
		cub->player.ray_angle += cub->player.angle_step;
		cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
		ray_count++;
	}
	
	printf("\nTotal rays: %d\n", ray_count);
	printf("=== RAY CASTING END ===\n\n");
}
