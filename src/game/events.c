/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:34:24 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/15 23:41:56 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	handle_close(void *param)
{
	(void)param;
	ft_free_all(nothing);
	return (0);
}
int	handle_key(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		move_forward(cub);
	else if (keycode == KEY_S)
		move_backward(cub);
	else if (keycode == KEY_A)
		move_left(cub);
	else if (keycode == KEY_D)
		move_right(cub);
	else if (keycode == KEY_LEFT)
		rotate(cub, LEFT);
	else if (keycode == KEY_RIGHT)
		rotate(cub, RIGHT);
	else if (keycode == KEY_ESC)
		ft_free_all(nothing);
	ray_casting(cub);
	return (0);
}
