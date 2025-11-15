/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:37:58 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/15 23:37:07 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_cub_file(char *filename)
{
	int	lenght;

	lenght = ft_strlen(filename);
	if (lenght > 4 && (ft_strcmp(filename + lenght - 4, ".cub") == 0))
		return (0);
	return (1);
}

void	flood_fill(t_cub *cub, int i, int j, bool is_zero)
{
	int	len_row;

	if (i > 0 && i < cub->game.height && cub->map_prsv[i])
		len_row = cub->rows[i];
	if (is_zero && (j < 0 || j >= len_row || i < 0 || i >= cub->game.height
			|| !cub->map_prsv[i] || cub->map_prsv[i][j] == ' ' || !cub->map_prsv[i][j]
			|| cub->map_prsv[i][j] == '\t'))
		ft_free_all(wall);
	if (j < 0 || j >= len_row || i < 0 || i >= cub->game.height || !cub->map_prsv[i]
		|| !cub->map_prsv[i][j] || cub->map_prsv[i][j] == '1' || cub->map_prsv[i][j] == 'F')
	{
		is_zero = false;
		return ;
	}
	is_zero = true;
	cub->map_prsv[i][j] = 'F';
	flood_fill(cub, i + 1, j, is_zero);
	flood_fill(cub, i - 1, j, is_zero);
	flood_fill(cub, i, j + 1, is_zero);
	flood_fill(cub, i, j - 1, is_zero);
}

void	c_check_element(t_cub *cub, int i, int j)
{
	if (cub->game.width <= j)
		cub->game.width = j + 1;
	if ((cub->map[i][j] == 'W' || cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
			|| cub->map[i][j] == 'E') && !cub->config.position_player)
	{
		cub->config.position_player = cub->map[i][j];
		cub->player.x = j * TILE;
		cub->player.y = i * TILE;
		flood_fill(cub, i, j, false);
	}
	else if (cub->map[i][j] != '0' && cub->map[i][j] != '1')
		ft_free_all(element);
}

void	check_element(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			c_check_element(cub, i, j);
			j++;
		}
		i++;
	}
	if (!cub->config.position_player)
		ft_free_all(element);
}

bool	parse_cub_file(char *filename, t_cub *cub)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_free_all(nothing);
	read_lines(fd, cub, filename);
	check_element(cub);
	return (0);
}
