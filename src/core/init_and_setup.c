/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:06:54 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/15 23:39:01 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	texture_init(t_cub *cub)
{
	// todo protect against invalid texture paths
	cub->texture[0].img = mlx_xpm_file_to_image(cub->game.mlx,
			cub->config.no_texture, &cub->texture[0].width,
			&cub->texture[0].height);
	cub->texture[1].img = mlx_xpm_file_to_image(cub->game.mlx,
			cub->config.so_texture, &cub->texture[1].width,
			&cub->texture[1].height);
	cub->texture[2].img = mlx_xpm_file_to_image(cub->game.mlx,
			cub->config.we_texture, &cub->texture[2].width,
			&cub->texture[2].height);
	cub->texture[3].img = mlx_xpm_file_to_image(cub->game.mlx,
			cub->config.ea_texture, &cub->texture[3].width,
			&cub->texture[3].height);
	if (!cub->texture[0].img || !cub->texture[1].img || !cub->texture[2].img
		|| !cub->texture[3].img)
		ft_free_all(mlx);
	cub->texture[0].img_add = mlx_get_data_addr(cub->texture[0].img,
			&cub->texture[0].bpp, &cub->texture[0].size_line,
			&cub->texture[0].endian);
	cub->texture[1].img_add = mlx_get_data_addr(cub->texture[1].img,
			&cub->texture[1].bpp, &cub->texture[1].size_line,
			&cub->texture[1].endian);
	cub->texture[2].img_add = mlx_get_data_addr(cub->texture[2].img,
			&cub->texture[2].bpp, &cub->texture[2].size_line,
			&cub->texture[2].endian);
	cub->texture[3].img_add = mlx_get_data_addr(cub->texture[3].img,
			&cub->texture[3].bpp, &cub->texture[3].size_line,
			&cub->texture[3].endian);
	if (!cub->texture[0].img_add || !cub->texture[1].img_add
		|| !cub->texture[2].img_add || !cub->texture[3].img_add)
		ft_free_all(mlx);
}

void	mlx_init_and_setup(t_cub *cub)
{
	cub->game.win = mlx_new_window(cub->game.mlx, cub->game.width_t,
			cub->game.height_t, "ghorayr");
	if (!cub->game.win)
		ft_free_all(mlx);
	cub->game.img = mlx_new_image(cub->game.mlx, cub->game.width_t,
			cub->game.height_t);
	if (!cub->game.img)
		ft_free_all(mlx);
	cub->game.img_data = mlx_get_data_addr(cub->game.img, &cub->game.bpp,
			&cub->game.size_line, &cub->game.endian);
	texture_init(cub);
	ray_casting(cub);
	mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
}

void	init_mlx_fun(t_cub *cub)
{
	init_player(cub);
	cub->game.mlx = mlx_init();
	if (!cub->game.mlx) // todo checkk all the mlx return values
		ft_free_all(mlx);
	mlx_init_and_setup(cub);
	mlx_hook(cub->game.win, 2, 1L << 0, handle_key, cub);
	mlx_hook(cub->game.win, 17, 0, handle_close, NULL);
	mlx_loop(cub->game.mlx);
}
