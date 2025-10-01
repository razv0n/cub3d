// # Reads all lines from .cub file
#include "../../cub3d.h"


int read_lines(int fd)
{
	t_lines *head = NULL;
	t_lines *tmp = NULL;

	char *line;
	while((line = get_next_line(fd)))
	{
		t_lines *new_node = malloc(sizeof(t_lines));
		if(!new_node)
			return (1);
		new_node->content = line;
		new_node->next = NULL;
		if(!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
	}
	close(fd);

	// t_lines *tmp2 = head;
	// while(tmp2)
	// {
	// 	printf("%s", tmp2->content);
	// 	tmp2 = tmp2->next;
	// }
	return 0;
}