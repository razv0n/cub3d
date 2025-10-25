#include "../../cub3d.h"

int is_cub_file(char *filename)
{
	int lenght;
	
	lenght = ft_strlen(filename);
	if(lenght > 4 && (ft_strcmp(filename + lenght - 4, ".cub") == 0))
		return(0);
	return(1);
}
void	check_error_wall(int i, int j, t_cub *cub)
{
	if (cub->map[i][j] != '1' && cub->map[i][j] != '\n')
	{
		ft_free_all(cub);
		exit(printf("Error\nState Of Wall\n"));
	}
}
void	check_the_state_of_wall(t_cub *cub, int length_map)
{
	int (i), (j), (row_length);
	i = 0;

	while (cub->map[i])
	{
		j = 0;
		row_length = ft_strlen(cub->map[i]) - 2;
		while (cub->map[i][j])
		{
			if (!i || i == length_map - 1)
				check_error_wall(i, j, cub);
			else
			{
				if (cub->map[i][0] == '1' && cub->map[i][row_length] == '1')
					break ;
				else
				{
					ft_free_all(cub);
					exit(printf("Error\nState Of Wall\n"));
				}
			}
			j++;
		}
		i++;
	}
}


void	check_element(t_cub *cub)
{
	int i;
	int j;
	int length_row;

	i = 0;
	while(cub->map[i])
	{
		j = 1;
		length_row = ft_strlen(cub->map[i]) - 2;
		while(j <= length_row)
		{
			if (cub->game->width <= j)
				cub->game->width = j;
			if ((cub->map[i][j] == 'W' || cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || cub->map[i][j] == 'E') && !cub->config.position_player)
				cub->config.position_player = cub->map[i][j];
			else if (cub->map[i][j] != '0' && cub->map[i][j] != '1' && cub->map[i][j] != '\n')
				exit(printf("free all"));
			j++;
		}
		i++;
	}
}
void	made_map(t_cub *cub)
{
	int		length;
	int	length_map;

	length_map = 0;
	length = cub->first_index_map;
	while(cub->all_map[length])
	{
		if (cub->all_map[length][0])
			length_map++;
		length++;
	}
	cub->map = ft_malloc(sizeof(char *) * (length_map + 1));
	length = cub->first_index_map;
	length_map = 0;
	while(cub->all_map[length])
	{
		if (cub->all_map[length][0])
			cub->map[length_map++] = cub->all_map[length];
		length++;
	}
	cub->map[length_map] = NULL;
	cub->game->height = length_map;
	check_the_state_of_wall(cub, length_map);
	check_element(cub);
}

int parse_cub_file(char *filename, t_cub *cub)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
		ft_free_all();
	read_lines(fd, cub, filename);
	made_map(cub);
	return (0);
}