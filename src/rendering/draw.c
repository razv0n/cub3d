/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/25 16:36:26 by mfahmi           ###   ########.fr       */
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

void draw_map(t_cub *cub)
{
    int y = 0;
    while (cub->map[y])
    {
        int x = 0;
        while (cub->map[y][x])
        {
            if (cub->map[y][x] == '1')
                draw_sq(cub->game, x, y, 0xFFFFFF);
            else if (cub->map[y][x] == '0')
                draw_sq(cub->game, x, y, 0x000000);
            else if (cub->map[y][x] != '\n')
                draw_sq(cub->game, x, y, 0x00FF00);
            x++;
        }
        y++;
    }
}
