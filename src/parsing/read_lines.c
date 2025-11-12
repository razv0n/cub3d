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
		free(line); //  remove this 
		line = get_next_line(fd);
	}
	close(fd);
	return (length);
}

void	read_lines(int fd, t_cub *cub, char *filename)
{
	char *line;
	bool  check;

	check = true;
	// printf("%d\n", cub->index_a_map);
	cub->index_a_map = 0;
	cub->all_map = ft_malloc(sizeof(char *) * (lenght_map(fd) + 1));
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		check = check_rules_map(&line, cub);	
		if (cub->nm_line < 7 || !check)
			cub->all_map[cub->index_a_map] = line; // ?why i store the line here
		cub->index_a_map++;
		line = get_next_line(fd);
	}
	close(fd);
	cub->all_map[cub->index_a_map] = NULL;
}
