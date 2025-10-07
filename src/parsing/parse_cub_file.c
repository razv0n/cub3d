 #include "../../cub3d.h"

int is_cub_file(char *filename)
{
	int lenght;
	
	lenght = ft_strlen(filename);
	if(lenght > 4 && (ft_strcmp(filename + lenght - 4, ".cub") == 0))
		return(0);
	return(1);
}

bool	check_the_state_of_wall(t_cub *cub)
{
	int (i), (j), (lenght);

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		lenght = ft_strlen(cub->map[i]);
		while (cub->map[i][j])
		{
			if (!i || i == cub->index_a_map - 1)
				check_error_wall(i, j, cub);
			else
			{
				if (cub->map[0] == '1' && cub->map[lenght - 1] == '1')
					break ;
				else
				{
					free_data(cub);
					exit(ft_print("Error\nState Of Wall\n", 2));
				}
			}
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
	length = cub->index_a_map - cub->first_index_map;
	while(cub->all_map[length])
	{
		if (cub->all_map[length][0])
			length_map++;
		length++;
	}
	length = cub->index_a_map - cub->first_index_map;
	length_map = 0;
	cub->map = malloc(sizeof(char *) * (length_map + 1));
	while(cub->all_map[length])
	{
		if (cub->all_map[length][0])
			cub->map[length_map++] = cub->all_map[length];
		length++;
	}
	check_the_state_of_wall(cub);
}

int parse_cub_file(char *filename, t_cub *cub)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
		perror("free all and exit \n");
	read_lines(fd, cub);
	made_map(cub);
	return (0);
}

