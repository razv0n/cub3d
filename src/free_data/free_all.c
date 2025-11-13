/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:45:40 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/13 10:36:35 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../cub3d.h"

void    ft_free_all()
{
    t_list **head;
    t_cub *cub;

    head = return_ptr();
    if (!head || !*head)
        return;
    cub = (t_cub*)(*head)->content;
    if (cub)
        free_mlx_data(cub);
    ft_lstclear(head, free);
    exit(0);
}

void    free_mlx_data(t_cub *cub)
{
    if (!cub)
        return;
    if(cub->game.mlx && cub->game.img)
        mlx_destroy_image(cub->game.mlx, cub->game.img);
    if(cub->game.mlx && cub->game.win)
        mlx_destroy_window(cub->game.mlx, cub->game.win);
    cub->game.mlx = NULL;
}
