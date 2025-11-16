/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotation_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:50:20 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/16 10:25:44 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	move_forward(t_cub *cub)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.x + (cub->player.dir_x * cub->player.move_speed);
	next_y = cub->player.y + (cub->player.dir_y * cub->player.move_speed);
	if (is_walkable(cub, next_x + (0.1 * TILE), next_y) && is_walkable(cub,
			next_x, next_y + (0.1 * TILE)) && is_walkable(cub, next_x - (0.1
				* TILE), next_y) && is_walkable(cub, next_x, next_y - (0.1
				* TILE)))
	{
		cub->player.x = next_x;
		cub->player.y = next_y;
	}
}

void	move_backward(t_cub *cub)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.x - (cub->player.dir_x * cub->player.move_speed);
	next_y = cub->player.y - (cub->player.dir_y * cub->player.move_speed);
	if (is_walkable(cub, next_x - (0.1 * TILE), next_y) && is_walkable(cub,
			next_x, next_y - (0.1 * TILE)) && is_walkable(cub, next_x + (0.1
				* TILE), next_y) && is_walkable(cub, next_x, next_y + (0.1
				* TILE)))
	{
		cub->player.x = next_x;
		cub->player.y = next_y;
		return ;
	}
	if (is_walkable(cub, next_x, cub->player.y))
		cub->player.x = next_x;
	if (is_walkable(cub, cub->player.x, next_y))
		cub->player.y = next_y;
}

void	move_right(t_cub *cub)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.x + cub->player.dir_y * cub->player.move_speed;
	next_y = cub->player.y - cub->player.dir_x * cub->player.move_speed;
	if (is_walkable(cub, next_x + (0.1 * TILE), next_y) && is_walkable(cub,
			next_x, next_y - (0.1 * TILE)) && is_walkable(cub, next_x - (0.1
				* TILE), next_y) && is_walkable(cub, next_x, next_y + (0.1
				* TILE)))
	{
		cub->player.x = next_x;
		cub->player.y = next_y;
	}
}

void	rotate(t_cub *cub, t_direction dir)
{
	if (dir == RIGHT)
	{
		cub->player.player_angle += cub->player.rot_speed;
		cub->player.player_angle = normalize_angle(cub->player.player_angle);
		update_player_dir(cub);
	}
	else
	{
		cub->player.player_angle -= cub->player.rot_speed;
		cub->player.player_angle = normalize_angle(cub->player.player_angle);
		update_player_dir(cub);
	}
}

void	move_left(t_cub *cub)
{
	double	next_x;
	double	next_y;

	next_x = cub->player.x - cub->player.dir_y * cub->player.move_speed;
	next_y = cub->player.y + cub->player.dir_x * cub->player.move_speed;
	if (is_walkable(cub, next_x - (0.1 * TILE), next_y + (0.1 * TILE))
		&& is_walkable(cub, next_x, next_y - (0.1 * TILE)) && is_walkable(cub,
			next_x + (0.1 * TILE), next_y) && is_walkable(cub, next_x, next_y
			+ (0.1 * TILE)))
	{
		cub->player.x = next_x;
		cub->player.y = next_y;
	}
}
