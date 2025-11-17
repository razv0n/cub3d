/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_and_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:12:34 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/17 18:00:48 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_so_no(char *line, t_cub *cub, bool *no, bool *so)
{
	if (!ft_strncmp(line, "SO", 2) && !*so)
	{
		if (!*(line + 2))
			ft_free_all(wall);
		cub->config.so_texture = line + 2;
		*so = true;
	}
	else if (!ft_strncmp(line, "NO", 2) && !*no)
	{
		if (!*(line + 2))
			ft_free_all(wall);
		cub->config.no_texture = line + 2;
		*no = true;
	}
}

void	check_ea_we(char *line, t_cub *cub, bool *ea, bool *we)
{
	if (!ft_strncmp(line, "EA", 2) && !*ea)
	{
		if (!*(line + 2))
			ft_free_all(wall);
		cub->config.ea_texture = line + 2;
		*ea = true;
	}
	else if (!ft_strncmp(line, "WE", 2) && !*we)
	{
		if (!*(line + 2))
			ft_free_all(wall);
		cub->config.we_texture = line + 2;
		*we = true;
	}
}

bool	check_the_texture_wall(char *line, short nm_line, t_cub *cub)
{
	static bool	no;
	static bool	so;
	static bool	ea;
	static bool	we;

	check_so_no(line, cub, &no, &so);
	check_ea_we(line, cub, &ea, &we);
	if (nm_line == 4)
		return (no & so & ea & we);
	return (true);
}
