// # Key/mouse hooks 

#include "../../cub3d.h"

int handle_close()
{
    ft_free_all();
    return (0);
}

int key_press(t_cub *cub, int keycode)
{
    if(keycode == KEY_ESC)
        return (handle_close());
    cub->game->keys[keycode] = 1;
    return (0);
}

// user Input → key_press() → keys[] updated
//                 ↓
//          game_loop() runs every frame
//                 ↓
//          Checks keys[] array
//                 ↓
//          Calls move_player() if needed
//                 ↓
//          Redraws screen
