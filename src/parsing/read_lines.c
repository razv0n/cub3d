#include "../../cub3d.h"

int	lenght_map(int fd)
{
	char	*line;
	int 	length;

	length = 0;
	line = get_next_line(fd);
	while (line)
	{
		length++;
		free(line);
		line = get_next_line(fd);
	}
	return (length);
}

void	read_lines(int fd, t_cub *cub)
{
	char *line;
	
	cub->index_a_map = 0;
	cub->all_map = malloc(sizeof(char *) * (lenght_map(fd) + 1)); // use ft_malloc();
	if (!cub->all_map)
		perror("leaks here :): \n");
	line = get_next_line(fd);
	while(line)
	{
		cub->all_map[cub->index_a_map] = line;
		check_rules_map(&line, cub);
		cub->index_a_map++;
		line = get_next_line(fd);
	}
	cub->all_map[cub->index_a_map] = NULL;
}
