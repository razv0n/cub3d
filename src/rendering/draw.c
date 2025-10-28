/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/28 17:09:38 by mfahmi           ###   ########.fr       */
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


void    ray_casting(t_cub *cub)
{
    int     i;
    double  player_angle;
    double  ray_angle;
    double  angle_step;
    double ray_dir_x;
    double ray_dir_y;
    // const float step;
    double x;
    double y;

    
    // step
    player_angle = atan2(cub->player.dir_y, cub->player.dir_x);
    ray_angle = player_angle - (FOV / 2);
    angle_step = FOV / cub->game->width;
    // x = cub->player.x;
    // y = cub->player.y;
    i = 0;
    while (i < cub->game->width)
    {
        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);
        x = cub->player.x;
        y = cub->player.y;
        while (is_walkable(cub, (int)x, (int)y))
        {
            // if (is_walkable(cub, (int)x, (int)y))
            //     break;
            x += ray_dir_x * 0.01;
            y += ray_dir_y * 0.01;
            put_pixel(cub, (int)(x * SQUARE) + 6, (int)(y * SQUARE) + 6, 0x0000FF);
        }
        ray_angle += angle_step;
        i++;
    }
}
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
