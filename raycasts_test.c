#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h> // For exit()

#define ROT_SPEED 0.01 // A small value for a smooth rotation speed
#define MOVE_SPEED 0.03 // A small value for a smooth movement speed

// A simple pixel put function to draw on the image buffer
void put_pixel_to_img(t_data *data, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
    {
        dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

// The main raycasting and 3D rendering function
void raycast(t_data *data)
{
    // A loop to cast a ray for every pixel of the screen's width
    for (int x = 0; x < WIN_W; x++)
    {
        // calculate ray position and direction in camera space
        double cameraX = 2 * x / (double)WIN_W - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        double deltaDistX;
        double deltaDistY;

        if (rayDirX == 0) {
            deltaDistX = 1e30;
        } else {
            deltaDistX = fabs(1 / rayDirX);
        }
        if (rayDirY == 0) {
            deltaDistY = 1e30;
        } else {
            deltaDistY = fabs(1 / rayDirY);
        }

        double sideDistX;
        double sideDistY;
        int stepX;
        int stepY;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (data->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (data->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
        }

        int hit = 0;
        int side;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (data->worldMap[mapY][mapX] > 0)
                hit = 1;
        }

        // Calculate the perpendicular distance to the wall to prevent fisheye
        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        // Calculate height of line to draw on screen
        int lineHeight = (int)(WIN_H / perpWallDist);

        // Calculate the starting and ending pixel of the wall slice
        int drawStart = -lineHeight / 2 + WIN_H / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_H / 2;
        if (drawEnd >= WIN_H)
            drawEnd = WIN_H - 1;

        // Choose wall color based on side
        int color;
        if (side == 0)
            color = 0x07590f; // Red for vertical walls (E/W)
        else
            color = 0x05420b; // Dark red for horizontal walls (N/S)

        // Draw the wall slice
        for (int y = drawStart; y < drawEnd; y++)
        {
            put_pixel_to_img(data, x, y, color);
        }
        
        // Draw floor and ceiling
        // You can add more complex floor and ceiling textures later
        for(int y = drawEnd; y < WIN_H; y++)
        {
            put_pixel_to_img(data, x, y, 0x4B371C); // Brown floor
        }
        for(int y = 0; y < drawStart; y++)
        {
            put_pixel_to_img(data, x, y, 0x40c9b9); // Grey ceiling
        }
    }
}

// Handles key press events, setting the rotation and movement state
int key_press(int keycode, t_data *data)
{
    // Escape key to exit the program
    if (keycode == 53)
        exit(0);

    // Left arrow key
    if (keycode == 65361)
        data->is_rotating_left = 1;
    
    // Right arrow key
    if (keycode == 65363)
        data->is_rotating_right = 1;

    // Up arrow key
    if (keycode == 65362)
        data->is_moving_forward = 1;
    
    // Down arrow key
    if (keycode == 65364)
        data->is_moving_backward = 1;
    
    return (0);
}

// Handles key release events, resetting the rotation and movement state
int key_release(int keycode, t_data *data)
{
    // Left arrow key
    if (keycode == 65361)
        data->is_rotating_left = 0;
    
    // Right arrow key
    if (keycode == 65363)
        data->is_rotating_right = 0;

    // Up arrow key
    if (keycode == 65362)
        data->is_moving_forward = 0;

    // Down arrow key
    if (keycode == 65364)
        data->is_moving_backward = 0;
    
    return (0);
}

// Handles window close event
int close_window(t_data *data)
{
    (void)data; // Cast to void to avoid unused parameter warning
    exit(0);
    return (0);
}

// The main rendering loop function, called by mlx_loop_hook
int render(t_data *data)
{
    // Continuous rotation logic
    if (data->is_rotating_left)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(-ROT_SPEED) - data->dirY * sin(-ROT_SPEED);
        data->dirY = oldDirX * sin(-ROT_SPEED) + data->dirY * cos(-ROT_SPEED);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(-ROT_SPEED) - data->planeY * sin(-ROT_SPEED);
        data->planeY = oldPlaneX * sin(-ROT_SPEED) + data->planeY * cos(-ROT_SPEED);
    }
    if (data->is_rotating_right)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(ROT_SPEED) - data->dirY * sin(ROT_SPEED);
        data->dirY = oldDirX * sin(ROT_SPEED) + data->dirY * cos(ROT_SPEED);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(ROT_SPEED) - data->planeY * sin(ROT_SPEED);
        data->planeY = oldPlaneX * sin(ROT_SPEED) + data->planeY * cos(ROT_SPEED);
    }

    // Continuous walking logic with basic collision detection
    if (data->is_moving_forward)
    {
        if (data->worldMap[(int)(data->posY + data->dirY * MOVE_SPEED)][(int)(data->posX)] == 0)
            data->posY += data->dirY * MOVE_SPEED;
        if (data->worldMap[(int)(data->posY)][(int)(data->posX + data->dirX * MOVE_SPEED)] == 0)
            data->posX += data->dirX * MOVE_SPEED;
    }

    if (data->is_moving_backward)
    {
        if (data->worldMap[(int)(data->posY - data->dirY * MOVE_SPEED)][(int)(data->posX)] == 0)
            data->posY -= data->dirY * MOVE_SPEED;
        if (data->worldMap[(int)(data->posY)][(int)(data->posX - data->dirX * MOVE_SPEED)] == 0)
            data->posX -= data->dirX * MOVE_SPEED;
    }

    // Clear the previous frame
    mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    
    // Call the updated raycast function to draw the 3D view
    raycast(data);
    
    // Put the final image to the window
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;

int worldMap[12][24] = {
		// A sample map, where 1 is a wall and 0 is an empty space.
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
		{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};	


	for (int y = 0; y < MAP_SIZE_H; y++) {
        for (int x = 0; x < MAP_SIZE_W; x++) {
            data.worldMap[y][x] = worldMap[y][x];
        }
    }
    data.posX = 2.0; data.posY = 2.0;
    data.dirX = 1.0; data.dirY = 0.0;
    data.planeX = 0.0; data.planeY = 0.85;
    
    // Initialize key state
    data.is_rotating_left = 0;
    data.is_rotating_right = 0;
    data.is_moving_forward = 0;
    data.is_moving_backward = 0;

    // Initialize MLX and window
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "Cub3D - Raycaster");
    if (data.win_ptr == NULL)
        return (1);
    
    // Initialize image and get its address
    data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
    if (data.img.img_ptr == NULL)
        return (1);
    data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);

    // Set up the main loop hook
    mlx_loop_hook(data.mlx_ptr, &render, &data);
    
    // Set up the key press and release hooks for continuous action
    mlx_hook(data.win_ptr, 2, 1L << 0, &key_press, &data);
    mlx_hook(data.win_ptr, 3, 1L << 1, &key_release, &data);
    
    // Set up the window close hook
    mlx_hook(data.win_ptr, 17, 1L << 17, &close_window, &data);

    // Start the MLX loop
    mlx_loop(data.mlx_ptr);

    return (0);
}

