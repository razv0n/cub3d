//# Helpers for parsing config lines

#include "../../cub3d.h"

static int ft_atoi_byte(const char **str)
{
	int		r;

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

int     ft_strlen_remove(char *line)
{
    int i;
    int length;

    length = 0;
    i = 0;
    if (!line)
        return (0);
    while(line[i])
    {
        if (line[i] != ' ' && line[i] != '\t')
            length++;
        i++;
    }
    return (length);
}

char    *remove_char(char *line)
{
    char    *res;
    int        i;
    int       ir;
    
    if (!line)
        return NULL;
    res = malloc(sizeof(char) * (ft_strlen_remove(line) + 1));
    i = 0;
    ir = 0;
    while(line[i])
    {
        if (line[i] == ' ' || line[i] == '\t')
        {
            res[ir] = line[i];
            ir++;
        }
        i++;
    }
    res[ir] = '\0';
    return (res);
}

int     rbg_shift(short red, short blue, short green)
{
    return (red << 16 | blue << 8 | green);
}

bool    check_rbg(char *line, t_cub *cub, char RBG)
{
    short     rgb_arr[3];
    int              i;

    i = 0;
    if (!line)
        return (false);
    line = remove_char(line);
    while(ft_isdigit(*line)) // 10,3,234234
    {
            rgb_arr[i] = (short)ft_atoi_byte(&line);
            if (rgb_arr[i] == -1)
                return (false);
        i++;
        if (*line != ',')
            return false;
        line++;
    }
    if(*line != '\n')
        return (false);
    if(RBG == 'F')
        cub->config.floor_color = rbg_shift(rgb_arr[0], rgb_arr[1], rgb_arr[2]);
    else if(RBG == 'C')
        cub->config.ceiling_color = rbg_shift(rgb_arr[0], rgb_arr[1], rgb_arr[2]);
    return (true);
}

bool    check_the_texture_wall(char *line, short nm_line, t_cub *cub)
{
    static bool    no;
    static bool    so;
    static bool    ea;
    static bool    we;

    if (ft_strncmp(line, "NO", 2) && !no)
    {
        cub->config.no_texture = ft_strtrim(line + 2, " \t\n");
        if (*cub->config.no_texture)
            no = true;
    }
    else if (ft_strncmp(line, "SO", 2) && !so)
    {
        cub->config.so_texture = ft_strtrim(line + 2, " \t\n");
        if (*cub->config.so_texture)
            so = true;
    }
    else if (ft_strncmp(line, "EA", 2) && !ea)
    {
        cub->config.ea_texture = ft_strtrim(line + 2, " \t\n");
        if (*cub->config.ea_texture)
            ea = true;
    }
    else if (ft_strncmp(line, "WE", 2) && !we)
    {
        cub->config.we_texture = ft_strtrim(line + 2, " \t\n");
        if (*cub->config.we_texture)
            we = true;
    }
    else if (nm_line == 4)
        return (no & so & ea & we);

    return (true);
}

bool    check_the_colors(char *line, int nm_line, t_cub *cub)
{
    static bool f;
    static bool c;

    if (ft_strncmp("F", line, 1) && !f)
    {
        f = true;
        if (!check_rbg(line + 1, cub, 'F'))
            return (!f);
    }
    else if (ft_strncmp("C", line ,1) && !c)
    {
        c = true;
        if (!check_rbg(line + 1, cub, 'C'))
            return (!c);
    }
    return (c & f);
}

void   pars_map(char *line, t_cub *cub)
{
    bool        is_exist;
    
    if (!line)
        return false;
    cub->all_map[cub->index_a_map] = remove_char(line);
}

void    check_rules_map (char **line, t_cub *cub)
{
    static short    nm_line;

    nm_line = 0;
    while (**line == ' ' || **line == '\t' || **line == '\n')
        (*line)++;
    if (!**line)
        return;
    nm_line++;
    if (nm_line <= 4)
        if (!check_the_texture_wall(*line, nm_line, cub))
            perror("exit the programme and free !\n");
    else if(nm_line >= 5 && nm_line <= 6)
        if (!check_the_colors(*line, nm_line, cub))
            perror("exit the programme and free !\n");
    else
    {
        if (nm_line == 7)
            cub->first_index_map = cub->index_a_map;
        pars_map(*line, cub);
    }
}
