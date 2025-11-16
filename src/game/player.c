/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:34:53 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/16 14:32:11 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	is_walkable(t_cub *cub, double x_p, double y_p)
{
	int	x;
	int	y;

	x = x_p / TILE;
	y = y_p / TILE;
	if (y < 0 || x < 0 || y >= cub->game.height || x >= cub->game.width)
		return (0);
	if (!cub->map[y] || !cub->map[y][x])
		return (0);
	return (cub->map[y][x] != '1');
}

static void	c_set_player_direction(t_cub *cub, char dir)
{
	if (dir == 'E')
	{
		cub->player.dir_x = 1;
		cub->player.dir_y = 0;
		cub->player.player_angle = 0;
	}
	else if (dir == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.dir_y = 0;
		cub->player.player_angle = M_PI;
	}
}

 void	set_player_direction(t_cub *cub)
{
	char	dir;

	dir = cub->config.position_player;
	if (dir == 'N')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = -1;
		cub->player.player_angle = 3 * (M_PI / 2);
	}
	else if (dir == 'S')
	{
		cub->player.dir_x = 0;
		cub->player.dir_y = 1;
		cub->player.player_angle = M_PI / 2;
	}
	c_set_player_direction(cub, dir);
}

void	update_player_dir(t_cub *cub)
{
	cub->player.dir_x = cos(cub->player.player_angle);
	cub->player.dir_y = sin(cub->player.player_angle);
}

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
