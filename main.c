/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:46:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/02 09:50:40 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_cub cub;

	if(ac < 2)
		return(printf("Erorr\nCheck Program Arguments\n"), 1); //   
	if(is_cub_file(av[1]))
		return(printf("Erorr\nCheck File Extension\n"), 1);
	ft_memset(&cub, 0, sizeof(t_cub));
	if(parse_cub_file(av[1], &cub))
	return(printf("Error Parsing\n"), 1);
	cub.game = malloc(sizeof(t_game));
	ft_memset(cub.game, 0, sizeof(t_game));
	cub.game->mlx = mlx_init();
	if(!cub.game->mlx)
		//error
	mlx_init_and_setup(cub.game);  //      
    mlx_loop(cub.game->mlx);
}