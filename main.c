/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:46:41 by mowardan          #+#    #+#             */
/*   Updated: 2025/09/23 10:08:27 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_cub cub;

	if(ac < 2)
		return(printf("Check Program Arguments\n"), 1);
	if(is_cub_file(av[1]))
		return(printf("Check File Extension\n"), 1);
	ft_memset(&cub, 0, sizeof(t_cub));
	if(parse_cub_file(av[1], &cub))
		return(printf("Error Parsing\n"), 1);
	
}