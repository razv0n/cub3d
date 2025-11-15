/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/15 18:41:49 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	find_texture_x(t_cub *cub, t_texture texture)
{
	float	wallx;

	if (!cub->player.is_hr)
		wallx = cub->player.wall_hz_inter_y / TILE;
	else
		wallx = cub->player.wall_hz_inter_x / TILE;
	wallx -= floor(wallx);
	return ((int)(wallx * texture.width));
}

t_texture	what_is_texture(t_cub *cub)
{
	if (cub->player.is_hr && cub->game.face_up_down == UP)
		return (cub->texture[0]);
	else if (cub->player.is_hr && cub->game.face_up_down == DOWN)
		return (cub->texture[1]);
	else if (!cub->player.is_hr && cub->game.face_right_left == LEFT)
		return (cub->texture[2]);
	else if (!cub->player.is_hr && cub->game.face_right_left == RIGHT)
		return (cub->texture[3]);
	return (cub->texture[0]);
}

void	draw_texture(t_cub *cub, int ray_id, int wall_top, int wall_bottom)
{
	int			tex_x;
	int			y;
	int			tex_y;
	t_texture	texture;
	int			color;

	y = wall_top;
	texture = what_is_texture(cub);
	tex_x = find_texture_x(cub, texture);
	while (y < wall_bottom)
	{
		if (y >= 0 && y < cub->game.height_t)
		{
			tex_y = (int)(((y - wall_top) * (texture.height)
						/ cub->game.wall_height));
			color = get_pixel(texture, tex_x, tex_y);
			put_pixel(cub, ray_id, y, color);
		}
		y++;
	}
}

void	draw_wall_line(t_cub *cub, int ray_id)
{
	int		wall_top;
	int		wall_bottom;
	double	proj_plane_dist;
	int		y;

	cub->player.res_dist = cos(cub->player.ray_angle - cub->player.player_angle)
		* cub->player.res_dist;
	proj_plane_dist = cub->game.proj_plane_dist;
	cub->game.wall_height = (int)((TILE / cub->player.res_dist)
			* proj_plane_dist);
	wall_top = (cub->game.height_t / 2) - (cub->game.wall_height / 2);
	wall_bottom = wall_top + cub->game.wall_height;
	y = 0;
	while (y < wall_top && y < cub->game.height_t)
	{
		put_pixel(cub, ray_id, y, cub->config.ceiling_color);
		y++;
	}
	draw_texture(cub, ray_id, wall_top, wall_bottom);
	y = wall_bottom;
	while (y < cub->game.height_t)
	{
		put_pixel(cub, ray_id, y, cub->config.floor_color);
		y++;
	}
}
