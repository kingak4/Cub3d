/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:34:34 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/01 17:01:22 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// Window and map dimensions
# define WIN_W 1200
# define WIN_H 800
# define MAP_SIZE_W 24
# define MAP_SIZE_H 12
# define TILE_SIZE 30 // Size in pixels for each map tile

// A structure to hold all the data pointers and game state
typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    t_img   img;


	int is_rotating_left;
    int is_rotating_right;

    // Player and camera variables
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;

    // The world map
    int worldMap[MAP_SIZE_H][MAP_SIZE_W];
}   t_data;

// Function prototypes
int     render(t_data *data);
void    draw_grid(t_data *data);
void    raycast(t_data *data);
void    put_pixel_to_img(t_data *data, int x, int y, int color);
void    draw_line(t_data *data, double x1, double y1, double x2, double y2, int color);

#endif


/*
#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>

void raycast(int w);

#endif
*/
