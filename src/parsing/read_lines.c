/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:38:56 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/15 23:35:24 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	length_map(char *filename)
{
	int		fd;
	char	*line;
	int		length;

	fd = open(filename, O_RDONLY);
	length = 0;
	line = get_next_line(fd);
	while (line)
	{
		length++;
		line = get_next_line(fd);
	}
	close(fd);
	return (length);
}

void	read_lines(int fd, t_cub *cub, char *filename)
{
	char	*line;

	cub->index_map = 0;
	cub->length_map = length_map(filename);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		check_rules_map(&line, cub);
		cub->index_map++;
		line = get_next_line(fd);
	}
	if (!cub->map)
		ft_free_all(nothing);
	cub->map[cub->index_map] = NULL;
	cub->map_prsv[cub->index_map] = NULL;
	cub->game.height = cub->index_map;
	close(fd);
}
