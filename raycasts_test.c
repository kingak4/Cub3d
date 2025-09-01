#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h> // For exit()
#include <unistd.h>

#define ROT_SPEED 0.05 // A small value for a smooth rotation speed
#define MOVE_SPEED 0.05 // A small value for a smooth movement speed

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

// Draw a line using a basic DDA algorithm
void draw_line(t_data *data, double x1, double y1, double x2, double y2, int color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double step;
    
    if (fabs(dx) > fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);
    
    dx /= step;
    dy /= step;
    
    double x = x1;
    double y = y1;
    
    for (int i = 0; i <= step; i++)
    {
        put_pixel_to_img(data, (int)x, (int)y, color);
        x += dx;
        y += dy;
    }
}

// Draws the map grid on the image
void draw_grid(t_data *data)
{
    for (int y = 0; y < MAP_SIZE_H; y++)
    {
        for (int x = 0; x < MAP_SIZE_W; x++)
        {
            int color = 0xCCCCCC; // Grey for empty spaces
            if (data->worldMap[y][x] == 1)
                color = 0xFF0000; // Red for walls
            
            // Draw a filled square for each tile
            for (int i = 0; i < TILE_SIZE - 2; i++)
            {
                for (int j = 0; j < TILE_SIZE - 2; j++)
                {
                    put_pixel_to_img(data, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
                }
            }
        }
    }
}

// Draws a small blue square to represent the player's position
void draw_player(t_data *data)
{
    int player_size = 5;
    // Center the player square on the player's floating-point position
    int player_x_scaled = (int)(data->posX * TILE_SIZE - player_size / 2);
    int player_y_scaled = (int)(data->posY * TILE_SIZE - player_size / 2);

    for (int i = 0; i < player_size; i++)
    {
        for (int j = 0; j < player_size; j++)
        {
            put_pixel_to_img(data, player_x_scaled + i, player_y_scaled + j, 0x0000FF); // Blue color
        }
    }
}

// The raycasting function, now also drawing the ray
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
        
        // --- Drawing the ray ---
        // Calculate the exact hit point on the grid in world coordinates
        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        
        double endX = data->posX + rayDirX * perpWallDist;
        double endY = data->posY + rayDirY * perpWallDist;
        
        // Scale the coordinates to the visual grid, starting from the player's exact position
        double startX_scaled = data->posX * TILE_SIZE;
        double startY_scaled = data->posY * TILE_SIZE;
        double endX_scaled = endX * TILE_SIZE;
        double endY_scaled = endY * TILE_SIZE;

        draw_line(data, startX_scaled, startY_scaled, endX_scaled, endY_scaled, 0x00FF00); // Green ray
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
		usleep(15000);
    }
    if (data->is_rotating_right)
    {
        double oldDirX = data->dirX;
        data->dirX = data->dirX * cos(ROT_SPEED) - data->dirY * sin(ROT_SPEED);
        data->dirY = oldDirX * sin(ROT_SPEED) + data->dirY * cos(ROT_SPEED);
        double oldPlaneX = data->planeX;
        data->planeX = data->planeX * cos(ROT_SPEED) - data->planeY * sin(ROT_SPEED);
        data->planeY = oldPlaneX * sin(ROT_SPEED) + data->planeY * cos(ROT_SPEED);
		usleep(15000);
    }

    // Continuous walking logic with basic collision detection
    if (data->is_moving_forward)
    {
        if (data->worldMap[(int)(data->posY + data->dirY * MOVE_SPEED)][(int)(data->posX)] == 0)
            data->posY += data->dirY * MOVE_SPEED;
        if (data->worldMap[(int)(data->posY)][(int)(data->posX + data->dirX * MOVE_SPEED)] == 0)
            data->posX += data->dirX * MOVE_SPEED;
		usleep(15000);
    }

    if (data->is_moving_backward)
    {
        if (data->worldMap[(int)(data->posY - data->dirY * MOVE_SPEED)][(int)(data->posX)] == 0)
            data->posY -= data->dirY * MOVE_SPEED;
        if (data->worldMap[(int)(data->posY)][(int)(data->posX - data->dirX * MOVE_SPEED)] == 0)
            data->posX -= data->dirX * MOVE_SPEED;
		usleep(15000);
    }

    // Clear the previous frame
    mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    
    draw_grid(data);
    draw_player(data); // Draw the player on top of the grid
    raycast(data);
    
    // Put the final image to the window
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;

    // Initialize map and player variables
    for (int y = 0; y < MAP_SIZE_H; y++)
    {
        for (int x = 0; x < MAP_SIZE_W; x++)
        {
            data.worldMap[y][x] = 0;
            if (x == 0 || x == MAP_SIZE_W - 1 || y == 0 || y == MAP_SIZE_H - 1)
                data.worldMap[y][x] = 1;
        }
    }
    data.worldMap[2][2] = 1;
    data.worldMap[3][10] = 1;

    data.posX = 5.5; data.posY = 5.5;
    data.dirX = 1.0; data.dirY = 0.0;
    data.planeX = 0.0; data.planeY = 0.66;
    
    // Initialize key state
    data.is_rotating_left = 0;
    data.is_rotating_right = 0;
    data.is_moving_forward = 0;
    data.is_moving_backward = 0;

    // Initialize MLX and window
    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "Cub3D - Raycaster Grid");
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


/*
#include "cub3d.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void raycast(int w)
{
	
	// A conceptual map structure as a 2D array
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
	// Player and camera variables
	double posX = 20.0, posY = 2.0;       // x and y start position
	double dirX = -1.0, dirY = 0.0;         // initial direction vector
	double planeX = 0.0, planeY = 0.66;    // the 2D raycaster camera plane

	// The main game loop (e.g., in an mlx_loop_hook function)
	// A loop to cast a ray for every pixel of the screen's width
	for (int x = 0; x < w; x++)
	{
		// calculate ray position and direction in camera space
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		// Which box of the map the ray is in
		int mapX = (int)posX;
		int mapY = (int)posY;

		// Length of ray from one x or y-side to the next
		double deltaDistX;
		double deltaDistY;

		if (rayDirX == 0) {
			deltaDistX = 1e30; // a very large number to prevent division by zero
		}
	   	else 
		{
			deltaDistX = fabs(1 / rayDirX);
		}
		if (rayDirY == 0) 
		{
			deltaDistY = 1e30; // a very large number to prevent division by zero
		} 
		else 
		{
			deltaDistY = fabs(1 / rayDirY);
		}

		// Initial distances to next x or y-side and step direction
		double sideDistX;
		double sideDistY;
		int stepX;
		int stepY;

		// Calculate step direction and initial sideDist for X and Y
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		// DDA algorithm loop
		int hit = 0; // Was there a wall hit?
		int side;    // Was a NS or an EW wall hit?
		while (hit == 0)
		{
			// Jump to the next map square, either in the x-direction, or in y-direction
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

			// Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		// After the loop, the ray's distance to the wall and the wall's location are known.
		// You would then calculate the wall's height and draw it on the screen.
	}
}
*/
