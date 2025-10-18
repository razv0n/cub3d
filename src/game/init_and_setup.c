#include "../../cub3d.h"

// void    draw_img()
// {
//     while()
// }
void count_map(t_cub *cub)
{
    int rows = 0;
    int cols = 0;
    int len = 0;

    while(cub->map && cub->map[rows])
    {
        len = ft_strlen(cub->map[rows]);
        if(len > cols)
            cols = len;
        rows++;
    }
    cub->game->width = rows;
    cub->game->height = cols;
}

void mlx_init_and_setup(t_game *game)
{
    game->win = mlx_new_window(game->mlx, game->width, game->height, "cub");
    if(!game->win)
       perror("free the data");
    game->img = mlx_new_image(game->mlx, (game->height * SQUARE), (game->width * SQUARE));
    if(!game->img)
        exit(printf("Error\nCreating Image\n"));
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    // draw_img(game); // i need to do this funct to draw after this function i will put image to window with mlx_put_image_to_window
}

void    init_mlx_fun(t_cub *cub)
{
    cub->game = malloc(sizeof(t_game));
	ft_memset(cub->game, 0, sizeof(t_game));
	cub->game->mlx = mlx_init();
	if(!cub->game->mlx)
		perror("free the data and done");
	mlx_init_and_setup(cub->game);    
    mlx_loop(cub->game->mlx);
}