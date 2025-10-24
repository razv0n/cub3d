// # Player logic and movement

#include "cub3d.h"

static void find_player_position(t_cub *cub)
{
    int x;
    int y;

    x = 0;
    while (cub->map[x])
    {
        y = 0;
        while(cub->map[x][y])
        {
            if (cub->map[x][y] == cub->config.position_player)
            {
                cub->player.x = x + 0.5;
                cub->player.y = y + 0.5;
                return ;
            }
            y++;
        }
        x++;
    }
}

static void set_player_direction(t_cub *cub)
{
    char dir;

    dir = cub->config.position_player;
    if (dir == 'N')
    {
        
    }
    else if (dir == 'S')
    {
       
    }
    else if (dir == 'E')
    {
        
    }
    else if (dir == 'W')
    {
       
    }
}


int init_player(t_cub *cub)
{
    find_player_position(cub);
    set_player_direction(cub);
    cub->player.move_speed = 0.1;
    return (0);
}