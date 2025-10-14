#include "../../cub3d.h"

void count_map(t_cub *cub)
{
    int rows = 0;
    int cols = 0;
    int len = 0;

    while(cub->map && cub->map[rows])
    {
        len = ft_stlen(cub->map[rows]);
        if(len > cols)
            cols = len;
        rows++;
    }
    cub.game->width = rows;
    cub.game->height = cols;
}

void mlx_init_and_setup(t_game *game)
{
    game->win = mlx_new_window(game->mlx, game->width, game->height, "cub");
    if(!game->win)
        // error
    // create image buffer : Create a hidden image in memory with a pixel array 
    game->img = mlx_image(game->mlx, (game->height * SQUARE), (game->width * SQUARE));
    if(!game->image)
        //error
    game->img_data = mlx_get_data_addr(mlx->img, &game->bpp, &game->size_line, &game->endian);
    draw_img(game); // i need to do this funct to draw after this function i will put image to window with mlx_put_image_to_window
}