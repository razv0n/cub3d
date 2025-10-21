/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:45:40 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/21 11:55:59 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../cub3d.h"

void    ft_free_all()
{
    t_list **head;
    t_cub *cub;

    head = return_ptr();
    cub = (t_cub*)(*head)->content;  
    // free_mlx_data(cub);
    ft_lstclear(head, free);
}

// void    free_mlx_data(t_cub *cub)
// {
    // if (!)
// }