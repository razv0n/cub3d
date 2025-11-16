/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/16 10:18:12 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float	calc_dist(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	find_distance(t_cub *cub)
{
	double	dist_h;
	double	dist_v;

	dist_h = calc_dist(cub->player.x, cub->player.y,
			cub->player.wall_hz_inter_x, cub->player.wall_hz_inter_y);
	dist_v = calc_dist(cub->player.x, cub->player.y,
			cub->player.wall_vr_inter_x, cub->player.wall_vr_inter_y);
	if (dist_h < dist_v)
	{
		cub->player.res_dist = dist_h;
		cub->player.is_hr = true;
	}
	else
	{
		cub->player.wall_hz_inter_x = cub->player.wall_vr_inter_x;
		cub->player.wall_hz_inter_y = cub->player.wall_vr_inter_y;
		cub->player.res_dist = dist_v;
		cub->player.is_hr = false;
	}
}

void	check_dir(t_cub *cub)
{
	double	angle;

	angle = cub->player.ray_angle;
	if (angle > M_PI && angle < 2 * M_PI)
		cub->game.face_up_down = UP;
	else
		cub->game.face_up_down = DOWN;
	if (angle > M_PI / 2 && angle < (3 * M_PI) / 2)
		cub->game.face_right_left = LEFT;
	else
		cub->game.face_right_left = RIGHT;
}

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*ptr_img;

	if (x < 0 || y < 0 || x >= cub->game.width_t || y >= cub->game.height_t)
		return ;
	ptr_img = cub->game.img_data + ((y * cub->game.size_line) + (x
				* (cub->game.bpp / 8)));
	*(unsigned int *)ptr_img = color;
}

unsigned int	get_pixel(t_texture texture, int x, int y)
{
	char	*ptr_img;

	if (x < 0 || y < 0 || x >= texture.width || y >= texture.height)
		return (0);
	ptr_img = texture.img_add + ((y * texture.size_line) + (x * (texture.bpp
					/ 8)));
	return (*(unsigned int *)ptr_img);
}
