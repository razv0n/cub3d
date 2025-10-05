#include "../../cub3d.h"

int	lenght_map(int fd)
{
	char	*line;
	int 	length;

	length = 0;
	while (line = get_next_line(fd))
	{
		length++;
		free(line);
	}
	return (length);
}

char **read_lines(int fd, t_cub *cub)
{
	char *line;
	char **map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (lenght_map(fd) + 1)); // use ft_malloc();
	if (!map)
		perror("leaks here :): \n");
	while((line = get_next_line(fd)))
	{
		map[i] = line;
		check_rules_map(line, cub);
		i++;
	}
	map[i] = NULL;
	return map;
}
