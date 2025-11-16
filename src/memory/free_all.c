/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:45:40 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/16 10:25:05 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	check_message(t_msg mssg)
{
	if (mssg == wall)
		printf("Error\nInvalid Wall Texture Path\n");
	else if (mssg == color)
		printf("Error\nInvalid Color Format\n");
	else if (mssg == element)
		printf("Error\nInvalid Map Element\n");
	else if (mssg == mlx)
		printf("Error\nMLX Initialization Failed\n");
}

void	ft_free_all(t_msg message)
{
	t_list	**head;
	t_cub	*cub;

	check_message(message);
	head = return_ptr();
	if (!head || !*head)
		return ;
	cub = (t_cub *)(*head)->content;
	if (cub)
		free_mlx_data(cub);
	ft_lstclear(head, free);
	exit(0);
}

void	free_mlx_data(t_cub *cub)
{
	int	i;

	if (!cub || !cub->game.mlx)
		return ;
	if (cub->game.img)
		mlx_destroy_image(cub->game.mlx, cub->game.img);
	if (cub->game.win)
		mlx_destroy_window(cub->game.mlx, cub->game.win);
	if (cub->texture)
	{
		i = -1;
		while (++i < 4)
		{
			if (cub->texture[i].img)
			{
				mlx_destroy_image(cub->game.mlx, cub->texture[i].img);
				cub->texture[i].img = NULL;
			}
		}
	}
	if (cub->game.mlx)
	{
		mlx_destroy_display(cub->game.mlx);
		free(cub->game.mlx);
	}
}
