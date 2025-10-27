// # Player logic and movement

#include "../../cub3d.h"



static int is_walkable(t_cub *cub, int x, int y)
{
    if (y < 0 || x < 0)
        return (0);
    if (!cub->map[x] || !cub->map[x][y])
        return (0);
    // printf("the map [x][y] is %c   the x %d and y %d is \n",cub->map[x][y], x, y);
    return (cub->map[x][y] != '1');
}

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



//new position = current position + direction × speed


void    swap_value(t_cub *cub, double new_x, double new_y)
{
    char tmp;

    // tmp = cub->map[(int)cub->player.x];
    // cub->map[(int)cub->player.x] = cub->map[(int)new_x];
    // cub->map[(int)new_x] = tmp;
    // tmp = cub->map[(int)cub->player.y];
    // cub->map[(int)cub->player.y] = cub->map[(int)new_y];
    // cub->map[(int)new_y] = tmp;
    tmp = cub->map[(int)cub->player.x][(int)cub->player.y];
    cub->map[(int)cub->player.x][(int)cub->player.y] = cub->map[(int)new_x][(int)new_y];
    cub->map[(int)new_x][(int)new_y] = tmp;
    cub->player.x = new_x;
    cub->player.y = new_y;
}

void move_forward(t_cub *cub)
{
    double new_x;
    double new_y;

    new_x = cub->player.x + (cub->player.dir_x * cub->player.move_speed);
    new_y = cub->player.y + (cub->player.dir_y * cub->player.move_speed);
    printf("new x player: %f  new y player  %f    x player  : %f  y player  : %f\n", new_x, new_y , cub->player.x, cub->player.y);
    if (is_walkable(cub, (int)cub->player.x, (int)new_y))
        swap_value(cub, new_x, new_y);
}

void move_backward(t_cub *cub)
{
    double new_x;
    double new_y;

    new_x = cub->player.x - cub->player.dir_x * cub->player.move_speed;
    new_y = cub->player.y - cub->player.dir_y * cub->player.move_speed;
    if (is_walkable(cub, (int)cub->player.x, (int)new_y))
        swap_value(cub, new_x, new_y);

}

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

int handle_key( int keycode, t_cub *cub)
{
    // printf(" the x and the y of the player is : x =  %f y = %f\n", cub->player.x, cub->player.y);
    if (keycode == KEY_W)
        move_forward(cub);
    if (keycode == KEY_S)
        move_backward(cub);
    // Additional key handling (A, D, arrow keys) can be added here
    mlx_clear_window(cub->game->mlx, cub->game->win);
    draw_map(cub);
    mlx_put_image_to_window(cub->game->mlx, cub->game->win, cub->game->img, 0, 0);
    return (0);


}


void init_player(t_cub *cub)
{
    find_player_position(cub);
    set_player_direction(cub);
    cub->player.move_speed = 0.05;
    cub->player.rot_speed = 0.05;
    return;
}
