/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/09 21:40:05 by mfahmi           ###   ########.fr       */
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
    cub->game->width = 1000;
    cub->game->height = 1000;
}

void mlx_init_and_setup(t_cub *cub)
{
    t_game *game;

    game = cub->game;
    // game->width = 50;
    // game->height = 50;
    game->win = mlx_new_window(game->mlx, game->width * TILE, game->height * TILE, "ghorayr");
    if(!game->win)
        ft_free_all();
    // exit(1);
    printf("the gmae height : %d  the game width : %d \n", game->height, game->width);
    game->img = mlx_new_image(game->mlx, game->width * TILE, game->height * TILE);
    if(!game->img)
        ft_free_all();
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    init_player(cub);
    ray_casting(cub);
    // draw_map(cub);
    // draw_wall_line(cub);
    // mlx_put_img_to_window()
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    //  mlx_clear_window(cub->game->mlx, cub->game->win);
}

void    init_mlx_fun(t_cub *cub)
{
	cub->game->mlx = mlx_init();
	if(!cub->game->mlx)
		ft_free_all();
	mlx_init_and_setup(cub);
    // mlx_loop_hook(cub->game->mlx, (void *)ray_casting, cub);
    mlx_hook(cub->game->win, 2, 1L<<0, handle_key, cub);
    mlx_hook(cub->game->win, 17, 0, (void *)ft_free_all, cub);
    mlx_loop(cub->game->mlx);
}
