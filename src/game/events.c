/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:34:24 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/15 17:58:23 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	handle_close(void *param)
{
	(void)param;
	ft_free_all();
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
		ft_free_all();
	ray_casting(cub);
	return (0);
}
