/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:45:40 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/13 16:02:54 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_free_all(void)
{
	t_list	**head;

	t_cub *cub;
	head = return_ptr();
	if (!head || !*head)
		return ;
	cub = (t_cub*)(*head)->content;
	if (cub)
		free_mlx_data(cub);
	ft_lstclear(head, free);
	exit(0);
}

// void    free_mlx_data(t_cub *cub)
// {
//     // int i;

//     if (!cub || !cub->game.mlx)
//         return ;
//     if(!cub->texture)
//         return ;
//     if (cub->game.img)
//     {
//         mlx_destroy_image(cub->game.mlx, cub->game.img);
//         cub->game.img = NULL;
//     }
//     i = -1;
//     while (++i < 4)
//     {
//         if (cub->texture[i].img)
//         {
//             mlx_destroy_image(cub->game.mlx, cub->texture[i].img);
//             cub->texture[i].img = NULL;
//         }
//     }
//     if (cub->game.win)
//     {
//         mlx_destroy_window(cub->game.mlx, cub->game.win);
//         cub->game.win = NULL;
//     }
//     mlx_destroy_display(cub->game.mlx);
//     cub->game.mlx = NULL;
// }



void free_mlx_data(t_cub *cub)
{
	if(!cub || !cub->game.mlx)
		return ;
	if (cub->game.img)
		mlx_destroy_image(cub->game.mlx, cub->game.img);
	if(cub->game.win)
		mlx_destroy_window(cub->game.mlx, cub->game.win);
	if(cub->texture)
	{
		int i;

		i = -1;
		while(++i < 4)
		{
			if(cub->texture[i].img)
			{
				mlx_destroy_image(cub->game.mlx, cub->texture[i].img);
				cub->texture[i].img = NULL;
			}
		}
	}
	if(cub->game.mlx)
	{
		mlx_destroy_display(cub->game.mlx);
		free(cub->game.mlx);
	}
}
