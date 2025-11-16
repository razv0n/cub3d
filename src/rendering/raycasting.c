/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:38:41 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/16 10:17:55 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	calc_x_y_steps_horizontal(t_cub *cub)
{
	cub->game.step_y = TILE;
	if (cub->game.face_up_down == UP)
		cub->game.step_y = -TILE;
	cub->game.step_x = (cub->game.step_y) / tan(cub->player.ray_angle);
	if ((cub->game.face_right_left == LEFT && cub->game.step_x > 0)
		|| (cub->game.face_right_left == RIGHT && cub->game.step_x < 0))
		cub->game.step_x *= -1;
}

void	calc_x_y_steps_vertical(t_cub *cub)
{
	cub->game.step_x = TILE;
	if (cub->game.face_right_left == LEFT)
		cub->game.step_x = -TILE;
	cub->game.step_y = tan(cub->player.ray_angle) * cub->game.step_x;
	if ((cub->game.face_up_down == DOWN && cub->game.step_y < 0)
		|| (cub->game.face_up_down == UP && cub->game.step_y > 0))
		cub->game.step_y = -cub->game.step_y;
}

void	horizontal(t_cub *cub)
{
	double	check_y;
	double	x_inter;
	double	y_inter;

	y_inter = floor(cub->player.y / TILE) * TILE;
	if (cub->game.face_up_down == DOWN)
		y_inter += TILE;
	x_inter = cub->player.x + (y_inter - cub->player.y)
		/ tan(cub->player.ray_angle);
	calc_x_y_steps_horizontal(cub);
	while (1)
	{
		if (cub->game.face_up_down == UP)
			check_y = y_inter - 0.01;
		else
			check_y = y_inter + 0.01;
		if (!is_walkable(cub, x_inter, check_y))
			break ;
		x_inter += cub->game.step_x;
		y_inter += cub->game.step_y;
	}
	cub->player.wall_hz_inter_x = x_inter;
	cub->player.wall_hz_inter_y = y_inter;
}

void	vertical(t_cub *cub)
{
	double	check_x;
	double	x_inter;
	double	y_inter;

	x_inter = floor(cub->player.x / TILE) * TILE;
	if (cub->game.face_right_left == RIGHT)
		x_inter += TILE;
	y_inter = cub->player.y + (tan(cub->player.ray_angle) * (x_inter
				- cub->player.x));
	calc_x_y_steps_vertical(cub);
	while (1)
	{
		if (cub->game.face_right_left == LEFT)
			check_x = x_inter - 0.01;
		else
			check_x = x_inter + 0.01;
		if (!is_walkable(cub, check_x, y_inter))
			break ;
		x_inter += cub->game.step_x;
		y_inter += cub->game.step_y;
	}
	cub->player.wall_vr_inter_y = y_inter;
	cub->player.wall_vr_inter_x = x_inter;
}

void	ray_casting(t_cub *cub)
{
	int	ray_count;

	ray_count = 0;
	cub->player.ray_angle = cub->player.player_angle - (cub->game.fov / 2);
	cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
	cub->player.angle_step = cub->game.fov / cub->game.width_t;
	while (ray_count < cub->game.width_t)
	{
		check_dir(cub);
		horizontal(cub);
		vertical(cub);
		find_distance(cub);
		draw_wall_line(cub, ray_count);
		cub->player.ray_angle += cub->player.angle_step;
		cub->player.ray_angle = normalize_angle(cub->player.ray_angle);
		ray_count++;
	}
	mlx_put_image_to_window(cub->game.mlx, cub->game.win, cub->game.img, 0, 0);
}
