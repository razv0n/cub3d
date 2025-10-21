/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/21 14:57:06 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// void    draw_img()
// {
//     while()
// }
void count_map(t_cub *cub)
{
    int rows = 0;
    int cols = 0;
    int len = 0;

    while(cub->map && cub->map[rows])
    {
        len = ft_strlen(cub->map[rows]);
        if(len > cols)
            cols = len;
        rows++;
    }
    cub->game->width = rows;
    cub->game->height = cols;
}

void mlx_init_and_setup(t_cub *cub)
{
    t_game *game;

    game = cub->game;
    game->win = mlx_new_window(game->mlx, game->width, game->height, "cub");
    if(!game->win)
        ft_free_all();
    game->img = mlx_new_image(game->mlx, (game->height * SQUARE), (game->width * SQUARE));
    if(!game->img)
        ft_free_all();
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    draw_map(cub);
    // mlx_put_img_to_window()
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void    init_mlx_fun(t_cub *cub)
{
    cub->game = ft_malloc(sizeof(t_game));
	ft_memset(cub->game, 0, sizeof(t_game));
	cub->game->mlx = mlx_init();
	if(!cub->game->mlx)
		ft_free_all();
	mlx_init_and_setup(cub);
    mlx_loop(cub->game->mlx);
}