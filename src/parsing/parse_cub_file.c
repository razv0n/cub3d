 #include "../../cub3d.h"

int is_cub_file(char *filename)
{
	int lenght;
	
	lenght = ft_strlen(filename);
	if(lenght > 4 && (ft_strcmp(filename + lenght - 4, ".cub") == 0))
		return(0);
	return(1);
}

int parse_cub_file(char *filename, t_cub *cub)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if(fd < 0)
		perror("free all and exit \n");
	cub->all_map = read_lines(fd, cub);
	return (0);
}
