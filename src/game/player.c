// # Player logic and movement

#include "../../cub3d.h"

bool is_walkable(t_cub *cub, double x_p, double y_p)
{
    int x;
    int y;
    
    x = x_p / TILE; 
    y = y_p / TILE;
    
    // DEBUG: Show what we're checking
    // printf("    is_walkable(%.2f, %.2f) -> grid(%d,%d) = '%c'\n", 
    //        x_p, y_p, x, y, 
    //        (y >= 0 && x >= 0 && y < cub->game->height && x < cub->game->width && cub->map[y] && cub->map[y][x]) ? cub->map[y][x] : '?');
    
    if (y < 0 || x < 0 || y >= cub->game->height || x >= cub->game->width)
        return (0);
    if (!cub->map[y] || !cub->map[y][x])
        return (0);
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
                cub->player.x = (y + 0.5) * TILE;
                cub->player.y = (x + 0.5) * TILE;
                return ;
            }
            y++;
        }
        x++;
    }
}

void move_forward(t_cub *cub)
{
    double next_x;
    double next_y;

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
        cub->player.dir_x = -1;
        cub->player.dir_y = 0;
        cub->player.player_angle = M_PI;
    }
}

void rotate_left(t_cub *cub)
{
    double step;

    step = 1 * (M_PI / 180);
    cub->player.player_angle -= step;
    cub->player.player_angle = normalize_angle(cub->player.player_angle);
}

void rotate_right(t_cub *cub)
{
    double step;

    step = 1 * (M_PI / 180);
    cub->player.player_angle += step;
    cub->player.player_angle = normalize_angle(cub->player.player_angle);
}

int handle_key(int keycode, t_cub *cub)
{
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

double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return (angle);
}

void init_player(t_cub *cub)
{
    find_player_position(cub);
    set_player_direction(cub);
    cub->player.move_speed = 0.1 * TILE;
    cub->player.rot_speed = 3 * (M_PI / 180);
}
