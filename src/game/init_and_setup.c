/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/12 11:22:48 by mfahmi           ###   ########.fr       */
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
    cub->game.width = 1000;
    cub->game.height = 1000;
}
void texture_init(t_cub *cub)
{
    // todo protect against invalid texture paths
    cub->texture[0].img = mlx_xpm_file_to_image(cub->game.mlx, cub->config.no_texture, &cub->texture[0].width, &cub->texture[0].height);
    cub->texture[1].img = mlx_xpm_file_to_image(cub->game.mlx, cub->config.so_texture, &cub->texture[1].width, &cub->texture[1].height);
    cub->texture[2].img = mlx_xpm_file_to_image(cub->game.mlx, cub->config.we_texture, &cub->texture[2].width, &cub->texture[2].height);
    cub->texture[3].img = mlx_xpm_file_to_image(cub->game.mlx, cub->config.ea_texture, &cub->texture[3].width, &cub->texture[3].height);
    cub->texture[0].img_add = mlx_get_data_addr(cub->texture[0].img, &cub->texture[0].bpp, &cub->texture[0].size_line, &cub->texture[0].endian);
    cub->texture[1].img_add = mlx_get_data_addr(cub->texture[1].img, &cub->texture[1].bpp, &cub->texture[1].size_line, &cub->texture[1].endian);
    cub->texture[2].img_add = mlx_get_data_addr(cub->texture[2].img, &cub->texture[2].bpp, &cub->texture[2].size_line, &cub->texture[2].endian);
    cub->texture[3].img_add = mlx_get_data_addr(cub->texture[3].img, &cub->texture[3].bpp, &cub->texture[3].size_line, &cub->texture[3].endian);
}


void mlx_init_and_setup(t_cub *cub)
{
    cub->game.win = mlx_new_window(cub->game.mlx, cub->game.width * TILE, cub->game.height * TILE, "ghorayr");
    if(!cub->game.win)
        ft_free_all();
    // exit(1);
    printf("the gmae height : %d  the game width : %d \n", cub->game.height, cub->game.width);
    cub->game.img = mlx_new_image(cub->game.mlx, cub->game.width * TILE, cub->game.height * TILE);
    if(!cub->game.img)
        ft_free_all();
    cub->game.img_data = mlx_get_data_addr(cub->game.img, &cub->game.bpp, &cub->game.size_line, &cub->game.endian);
    init_player(cub); ///todo : change the name of it 
    texture_init(cub);
    ray_casting(cub);
    mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
}

// void load_textures(t_cub *cub)
// {
//     int w;
//     int h;
//     int i;
//     char *textures[4] = {cub->t_config.no_texture, cub->t_config.so_texture,
//                          cub->t_config.ea_texture, cub->t_config.we_texture};

//     i = 0;
//     while (i < 4)
//     {
//         if(!cub->game.textures[i])
//             return -1;
//         cub->game.img = mlx_xpm_file_to_image(cub->game.mlx, (char *)textures[i], &w, &h);
//         if(!cub->game.img)
//             return -1;
//         cub->game.img_data = mlx_get_data_addr(cub->game.img, &cub->game.bpp, &cub->game.size_line, &cub->game.endian);
//         i++;
//     }
//     return 0;
// }

void    init_mlx_fun(t_cub *cub)
{
	cub->game.mlx = mlx_init();
	if(!cub->game.mlx) // todo checkk all the mlx return values
		ft_free_all();
	mlx_init_and_setup(cub);
    // if(load_textures(cub) == -1)
    //     ft_free_all();
    mlx_hook(cub->game.win, 2, 1L<<0, handle_key, cub);
    mlx_hook(cub->game.win, 17, 0, (void *)ft_free_all, cub);
    mlx_loop(cub->game.mlx);
}
