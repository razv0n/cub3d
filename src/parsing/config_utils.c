/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:36:48 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/16 15:18:45 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_strlen_remove(char *line)
{
	int	i;
	int	length;

	length = 0;
	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			length++;
		i++;
	}
	return (length);
}

char	*remove_char(char *line)
{
	char	*res;
	int		i;
	int		ir;

	if (!line)
		return (NULL);
	res = ft_malloc(sizeof(char) * (ft_strlen_remove(line) + 1));
	i = 0;
	ir = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			res[ir] = line[i];
			ir++;
		}
		i++;
	}
	res[ir] = '\0';
	return (res);
}

void	parse_map(char *line, t_cub *cub)
{
	if (!line)
		return ;
	cub->map[cub->index_map] = line;
	cub->map_prsv[cub->index_map] = ft_strdup(cub->map[cub->index_map]);
	cub->rows[cub->index_map] = ft_strlen(cub->map[cub->index_map]);
}

void	check_rules_map(char **line, t_cub *cub)
{
	if(cub->nm_line < 7)
		*line = remove_char(*line);
	if (!**line)
		return;
	cub->nm_line++;
	if (cub->nm_line <= 4)
	{
		if (!check_the_texture_wall(*line, cub->nm_line, cub))
			ft_free_all(wall);
	}
	else if (cub->nm_line >= 5 && cub->nm_line <= 6)
	{
		if (!check_the_colors(*line, cub->nm_line, cub))
			ft_free_all(color);
	}
	else
	{
		if(cub->nm_line >= 7 && ft_strlen_remove(*line) == 0)
			ft_free_all(wall);
		if (cub->nm_line == 7)
		{
			cub->rows = ft_malloc(sizeof(int) * (cub->length_map
						- cub->index_map + 1));
			cub->map = ft_malloc(sizeof(char *) * (cub->length_map
						- cub->index_map + 2));
			cub->map_prsv = ft_malloc(sizeof(char *) * (cub->length_map
						- cub->index_map + 2));
			cub->index_map = 0;
		}
		parse_map(*line, cub);
	}
}
