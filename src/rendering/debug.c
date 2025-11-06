/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/06 01:24:10 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include <stdio.h>

void debug_player_info(t_cub *cub)
{
    printf("\n========== PLAYER INFO ==========\n");
    printf("Position (X, Y): (%.2f, %.2f)\n", cub->player.x, cub->player.y);
    printf("Grid Position: (%d, %d)\n", 
           (int)(cub->player.x / TILE), 
           (int)(cub->player.y / TILE));
    printf("Player Angle (rad): %.4f\n", cub->player.player_angle);
    printf("Player Angle (deg): %.2f°\n", cub->player.player_angle * 180.0 / M_PI);
    printf("Ray Angle (rad): %.4f\n", cub->player.ray_angle);
    printf("Ray Angle (deg): %.2f°\n", cub->player.ray_angle * 180.0 / M_PI);
    printf("Angle Step: %.6f\n", cub->player.angle_step);
    printf("=================================\n");
}

void debug_ray_info(t_cub *cub)
{
    printf("\n========== RAY CASTING INFO ==========\n");
    printf("Current Ray Angle (rad): %.4f\n", cub->player.ray_angle);
    printf("Current Ray Angle (deg): %.2f°\n", cub->player.ray_angle * 180.0 / M_PI);
    printf("FOV (rad): %.4f\n", FOV);
    printf("FOV (deg): %.2f°\n", FOV * 180.0 / M_PI);
    printf("\nHorizontal Intersection:\n");
    printf("  Wall Hit (X, Y): (%.2f, %.2f)\n", 
           cub->player.wall_hz_inter_x, 
           cub->player.wall_hz_inter_y);
    printf("  Grid Cell: (%d, %d)\n",
           (int)(cub->player.wall_hz_inter_x / TILE),
           (int)(cub->player.wall_hz_inter_y / TILE));
    printf("\nVertical Intersection:\n");
    printf("  Wall Hit (X, Y): (%.2f, %.2f)\n", 
           cub->player.wall_vr_inter_x, 
           cub->player.wall_vr_inter_y);
    printf("  Grid Cell: (%d, %d)\n",
           (int)(cub->player.wall_vr_inter_x / TILE),
           (int)(cub->player.wall_vr_inter_y / TILE));
    printf("\nResult Distance: %.2f\n", cub->player.res_dist);
    printf("======================================\n");
}

void debug_direction_info(t_cub *cub)
{
    printf("\n========== DIRECTION INFO ==========\n");
    printf("Face Up/Down: %s\n", cub->game->face_up_down == UP ? "UP" : "DOWN");
    printf("Face Right/Left: %s\n", cub->game->face_right_left == RIGHT ? "RIGHT" : "LEFT");
    printf("====================================\n");
}

void debug_map_info(t_cub *cub)
{
    int y = 0;
    
    printf("\n========== MAP INFO ==========\n");
    printf("Map Dimensions: %d x %d\n", cub->game->width, cub->game->height);
    printf("Tile Size: %d\n", TILE);
    printf("Total Map Size: %d x %d pixels\n", 
           cub->game->width * TILE, 
           cub->game->height * TILE);
    printf("\nMap Layout:\n");
    while (cub->map[y])
    {
        printf("Row %2d: [%s]\n", y, cub->map[y]);
        y++;
    }
    printf("==============================\n");
}

// void debug_config_info(t_cub *cub)
// {
//     printf("\n========== CONFIG INFO ==========\n");//     printf("Player Starting Position: %c\n", cub->config.position_player);
//     printf("North Texture: %s\n", cub->config.path_north ? cub->config.path_north : "NULL");
//     printf("South Texture: %s\n", cub->config.path_south ? cub->config.path_south : "NULL");
//     printf("West Texture: %s\n", cub->config.path_west ? cub->config.path_west : "NULL");
//     printf("East Texture: %s\n", cub->config.path_east ? cub->config.path_east : "NULL");
//     printf("Floor Color: 0x%06X\n", cub->config.floor_color);
//     printf("Ceiling Color: 0x%06X\n", cub->config.ceiling_color);
//     printf("=================================\n");
// }

void debug_game_state(t_cub *cub)
{
    printf("\n========== GAME STATE ==========\n");
    printf("Window Size: %d x %d\n", cub->game->width * TILE, cub->game->height * TILE);
    printf("Image BPP: %d\n", cub->game->bpp);
    printf("Size Line: %d\n", cub->game->size_line);
    printf("Endian: %d\n", cub->game->endian);
    printf("================================\n");
}

void debug_wall_check(t_cub *cub, double x, double y)
{
    int grid_x = (int)(x / TILE);
    int grid_y = (int)(y / TILE);
    
    printf("\n========== WALL CHECK ==========\n");
    printf("Checking Position: (%.2f, %.2f)\n", x, y);
    printf("Grid Position: (%d, %d)\n", grid_x, grid_y);
    
    if (grid_y >= 0 && grid_y < cub->game->height && 
        grid_x >= 0 && grid_x < (int)ft_strlen(cub->map[grid_y]))
    {
        printf("Map Cell: '%c'\n", cub->map[grid_y][grid_x]);
        printf("Is Walkable: %s\n", is_walkable(cub, x, y) ? "YES" : "NO");
    }
    else
    {
        printf("Position OUT OF BOUNDS!\n");
    }
    printf("================================\n");
}

void debug_distance_calculation(t_cub *cub)
{
    double dist_h = calc_dist(cub->player.x, cub->player.y, 
                              cub->player.wall_hz_inter_x, 
                              cub->player.wall_hz_inter_y);
    double dist_v = calc_dist(cub->player.x, cub->player.y, 
                              cub->player.wall_vr_inter_x, 
                              cub->player.wall_vr_inter_y);
    
    printf("\n========== DISTANCE CALC ==========\n");
    printf("Horizontal Distance: %.2f\n", dist_h);
    printf("Vertical Distance: %.2f\n", dist_v);
    printf("Selected Distance: %.2f\n", cub->player.res_dist);
    printf("Selected Type: %s\n", dist_h < dist_v ? "HORIZONTAL" : "VERTICAL");
    printf("===================================\n");
}

void debug_full_game(t_cub *cub)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           CUB3D COMPLETE GAME DEBUG INFO                   ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // debug_config_info(cub);
    debug_game_state(cub);
    debug_map_info(cub);
    debug_player_info(cub);
    debug_direction_info(cub);
    debug_ray_info(cub);
    debug_distance_calculation(cub);
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                    END OF DEBUG INFO                       ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void debug_ray_step(t_cub *cub, int ray_number)
{
    printf("\n========== RAY #%d ==========\n", ray_number);
    debug_direction_info(cub);
    debug_ray_info(cub);
    debug_distance_calculation(cub);
    printf("============================\n");
}
