/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:16:49 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/15 16:20:01 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	rbg_shift(short red, short blue, short green)
{
	return (red << 16 | green << 8 | blue);
}

bool	check_the_colors(char *line, int nm_line, t_cub *cub)
{
	static bool	f;
	static bool	c;

	if (!ft_strncmp("F", line, 1) && !f)
	{
		f = true;
		if (!check_rbg(line + 1, cub, 'F'))
			return (!f);
	}
	else if (!ft_strncmp("C", line, 1) && !c)
	{
		c = true;
		if (!check_rbg(line + 1, cub, 'C'))
			return (!c);
	}
	if (nm_line == 6)
		return (c & f);
	return (true);
}

static int	ft_atoi_byte(const char **str)
{
	int	r;

	r = 0;
	while (**str >= '0' && **str <= '9')
	{
		r = r * 10 + **str - '0';
		if (r > 255)
			return (-1);
		(*str)++;
	}
	return (r);
}

bool	check_rbg(char *line, t_cub *cub, char RBG)
{
	short	rgb_arr[3];
	int		i;

	i = 0;
	if (!line)
		return (false);       // todo check for the functions
	line = remove_char(line); // ramove all the withespaces
	while (ft_isdigit(*line))
	{
		rgb_arr[i] = (short)ft_atoi_byte((const char **)&line);
		if (rgb_arr[i] == -1)
			return (false);
		i++;
		if (*line != ',' && i != 3)
			return (false);
		line++;
	}
	if (*line)
		return (false);
	if (RBG == 'F')
		cub->config.floor_color = rbg_shift(rgb_arr[0], rgb_arr[1], rgb_arr[2]);
	else if (RBG == 'C')
		cub->config.ceiling_color = rbg_shift(rgb_arr[0], rgb_arr[1],
				rgb_arr[2]);
	return (true);
}
