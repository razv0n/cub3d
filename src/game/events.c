/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:34:24 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/13 14:18:10 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	handle_close(void)
{
	ft_free_all();
	return (0);
}

// int key_press(t_cub *cub, int keycode)
// {
//     if(keycode == KEY_ESC)
//         return (handle_close());
//     cub->game.keys[keycode] = 1;
//     return (0);
// }

// user Input → key_press() → keys[] updated
//                 ↓
//          game_loop() runs every frame
//                 ↓
//          Checks keys[] array
//                 ↓
//          Calls move_player() if needed
//                 ↓
//          Redraws screen

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
		rotate_left(cub);
	else if (keycode == KEY_RIGHT)
		rotate_right(cub);
	else if (keycode == KEY_ESC)
		ft_free_all();
	ray_casting(cub);
	return (0);
}
