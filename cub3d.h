#ifndef CUB3D_H
# define CUB3D_H

# define WIN_W 640
# define WIN_H 480
# define MAP_SIZE_W 24
# define MAP_SIZE_H 12
# define TEX_SIZE 128 // The size of our square textures (e.g., 64x64 pixels)

// A struct to hold a single image, used for textures and the main window buffer
typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_img;

// Main data structure to hold all game-related information
typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    t_img   img;
    int     worldMap[MAP_SIZE_H][MAP_SIZE_W];
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    
    // Player movement flags
    int     is_rotating_left;
    int     is_rotating_right;
    int     is_moving_forward;
    int     is_moving_backward;

    // Array of textures (North, South, East, West)
    t_img   textures[4];
}   t_data;

#endif

