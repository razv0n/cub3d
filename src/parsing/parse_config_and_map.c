/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_and_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:12:34 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/16 10:21:17 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_so_no(char *line, t_cub *cub, bool *no, bool *so)
{
	if (!ft_strncmp(line, "SO", 2) && !*so)
	{
		cub->config.so_texture = ft_strtrim(line + 2, " \t\n");
		if (*cub->config.so_texture)
			*so = true;
	}
	else if (!ft_strncmp(line, "NO", 2) && !*no)
	{
		cub->config.no_texture = ft_strtrim(line + 2, " \t\n");
		if (*cub->config.no_texture)
			*no = true;
	}
}

void	check_ea_we(char *line, t_cub *cub, bool *ea, bool *we)
{
	if (!ft_strncmp(line, "EA", 2) && !*ea)
	{
		cub->config.ea_texture = ft_strtrim(line + 2, " \t\n");
		if (*cub->config.ea_texture)
			*ea = true;
	}
	else if (!ft_strncmp(line, "WE", 2) && !*we)
	{
		cub->config.we_texture = ft_strtrim(line + 2, " \t\n");
		if (*cub->config.we_texture)
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
