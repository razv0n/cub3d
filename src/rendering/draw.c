/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:07:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/21 12:10:16 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# Drawing pixels walls

void    draw_map(t_cub *cub)
{
    int x;
    int y;

    x = 0;
    while (cub->map[x])
    {
        y = 0;
        while(cub->map[x][y])
        {
            if (cub->map[x][y] == '1')
            {
                
            }
            else if (cub->map[x][y] == '0')
            {

            }
            else if (cub->map[x][y] != '\n')
            {
                
            }
        }
    }
}