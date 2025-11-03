// # Player logic and movement

#include "../../cub3d.h"



 int is_walkable(t_cub *cub, double x_p, double y_p)
{
    int x;
    int y;

    x =  x_p / SQUARE; 
    y =  y_p / SQUARE;
    if (y < 0 || x < 0 || y >= cub->game->height || x >= cub->game->width)
        return (0);
    if (!cub->map[y] || !cub->map[y][x])
        return (0);
    // printf("the map [x][y] is %c   the x %d and y %d is \n",cub->map[x][y], x, y);
    return (cub->map[y][x] != '1');
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
                cub->player.y = (x + 0.5) * SQUARE;
                cub->player.x = (y + 0.5) * SQUARE;
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


void move_forward(t_cub *cub)
{
    double next_x;
    double next_y;


    printf("cub->player.dir_x : %.3f  cub->player.dir_y : %.3f \n", cub->player.dir_x, cub->player.dir_y);
    next_x = cub->player.x + (cub->player.dir_x * cub->player.move_speed);
    next_y = cub->player.y + (cub->player.dir_y * cub->player.move_speed);
    
    if (is_walkable(cub, next_x, next_y))
    {
        cub->player.x = next_x;
        cub->player.y = next_y;
    }
}
 

void move_backward(t_cub *cub)
{
    double next_x;
    double next_y;

    next_x = cub->player.x - (cub->player.dir_x * cub->player.move_speed);
    next_y = cub->player.y - (cub->player.dir_y * cub->player.move_speed);
    
    if (is_walkable(cub, next_x, next_y))
    {
        cub->player.x = next_x;
        cub->player.y = next_y;
        return;
    }
    
    if (is_walkable(cub, next_x, cub->player.y))
        cub->player.x = next_x;
    if (is_walkable(cub, cub->player.x, next_y))
        cub->player.y = next_y;
}

void move_left(t_cub *cub)
{
    double next_x;
    double next_y;

    next_x = cub->player.x - cub->player.dir_y * cub->player.move_speed;
    next_y = cub->player.y + cub->player.dir_x * cub->player.move_speed;
    if (is_walkable(cub, next_x, next_y))
    {
        cub->player.x = next_x;
        cub->player.y = next_y;
    }
}

void move_right(t_cub *cub)
{
    double next_x;
    double next_y;
    
    next_x = cub->player.x + cub->player.dir_y * cub->player.move_speed;
    next_y = cub->player.y - cub->player.dir_x * cub->player.move_speed;
    
    if (is_walkable(cub, next_x, next_y))
    {
        cub->player.x = next_x;
        cub->player.y = next_y;
    }
}

static void set_player_direction(t_cub *cub)
{
    char dir;

    dir = cub->config.position_player;
    if (dir == 'N')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = -1;
        cub->player.player_angle = 3 * (M_PI / 2);
    }
    else if (dir == 'S')
    {
        cub->player.dir_x = 0;
        cub->player.dir_y = 1;
        cub->player.player_angle = M_PI / 2;
    }
    else if (dir == 'E')
    {
        cub->player.dir_x = 1;
        cub->player.dir_y = 0;
        cub->player.player_angle = 0;
    }
    else if (dir == 'W')
    {
        cub->player.dir_y = 0;
        cub->player.dir_x = -1;
        cub->player.player_angle = M_PI;
    }
}

void rotate_left(t_cub *cub)
{
    double old_dir_x;

    old_dir_x = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(cub->player.rot_speed) - cub->player.dir_y * sin(cub->player.rot_speed);
    cub->player.dir_y = old_dir_x * sin(cub->player.rot_speed) + cub->player.dir_y * cos(cub->player.rot_speed);
    cub->player.player_angle = atan2(cub->player.dir_y, cub->player.dir_x);
}

void rotate_right(t_cub *cub)
{
     double old_dir_x;
     
    old_dir_x = cub->player.dir_x;
    cub->player.dir_x = cub->player.dir_x * cos(-cub->player.rot_speed) - cub->player.dir_y * sin(-cub->player.rot_speed);
    cub->player.dir_y = old_dir_x * sin(-cub->player.rot_speed) + cub->player.dir_y * cos(-cub->player.rot_speed);
    cub->player.player_angle = atan2(cub->player.dir_y, cub->player.dir_x);

}

int handle_key( int keycode, t_cub *cub)
{
    printf("Player position: x=%.3f y=%.3f dir_x=%.3f dir_y=%.3f\n", 
           cub->player.y, cub->player.x, cub->player.dir_x, cub->player.dir_y);
    if (keycode == KEY_W)
        move_forward(cub);
    else if (keycode == KEY_S)
        move_backward(cub);
    else if (keycode == KEY_A)
        move_left(cub);
    else if (keycode == KEY_D)
        move_right(cub);
    else if (keycode == KEY_LEFT)
        rotate_left(cub);
    else if (keycode == KEY_RIGHT)
        rotate_right(cub);
    else if (keycode == KEY_ESC)
        ft_free_all();
    
    mlx_clear_window(cub->game->mlx, cub->game->win);
    draw_map(cub);
    mlx_put_image_to_window(cub->game->mlx, cub->game->win, cub->game->img, 0, 0);
    return (0);
}

void init_player(t_cub *cub)
{
    find_player_position(cub);
    set_player_direction(cub);
    cub->player.move_speed = 0.1 * SQUARE;
    cub->player.rot_speed = 3 * (M_PI / 180);
    return;
}
