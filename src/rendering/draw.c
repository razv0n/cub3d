/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/27 15:01:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void put_pixel(t_game *game, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= game->width * SQUARE || y >= game->height * SQUARE)
        return;
    char *ptr_img = game->img_data + ((y * game->size_line) + (x * (game->bpp / 8)));
    *(unsigned int *)ptr_img = color;
}

void    draw_player(t_game *game, double x, double y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < 11)
    {
        j = 0;
        while(j < 11)
        {
            put_pixel(game, (int)(x * SQUARE) + i, (int)(y * SQUARE) + j, color);
            j++;
        }
        i++;
    }
}

void draw_sq(t_game *game, int x, int y,int color)
{
    int i;
    int j;

    i = 0;
    while (i < SQUARE)
    {
        j = 0;
        while(j < SQUARE)
        {
            put_pixel(game, x * SQUARE + i, y * SQUARE + j, color);
            j++;
        }
        i++;
    }
}

// void    draw_

void draw_map(t_cub *cub)
{
    int y = 0;
    while (cub->map[y])
    {
        int x = 0;
        while (x < cub->game->width)
        {
            if ((x >= (int)ft_strlen(cub->map[y]) && x < cub->game->width) || cub->map[y][x] == '1')
                draw_sq(cub->game, x, y, 0x00FFF0);
            else if (cub->map[y][x] == '0' || cub->map[y][x] == cub->config.position_player)
                draw_sq(cub->game, x, y , 0x000F00);
            // else
            x++;
        }
        y++;
    }
    draw_player(cub->game, cub->player.y, cub->player.x, 0x00FF00);
}
