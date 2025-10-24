// # Player logic and movement

#include "../../cub3d.h"

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


//        North (Up)
//        dir_y = -1
//             ↑
//             |
// West ←------+-----→ East
// dir_x=-1    |    dir_x=1
//             |
//             ↓
//         South (Down)
//         dir_y = 1

static void set_player_direction(t_cub *cub)
{
    char dir;

    dir = cub->config.position_player;
    if (dir == 'N')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = -1;
    }
    else if (dir == 'S')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = 1;
    }
    else if (dir == 'E')
    {
        cub->player.dir_x = 1;
        cub->player.dir_y = 0;
    }
    else if (dir == 'W')
    {
        cub->player.dir_y = 0;
        cub->player.dir_x = -1;
    }
}


void init_player(t_cub *cub)
{
    find_player_position(cub);
    set_player_direction(cub);
    cub->player.move_speed = 0.5;
    cub->player.rot_speed = 0.5;
    return;
}
