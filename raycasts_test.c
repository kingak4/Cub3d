#include "cub3d.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdlib.h> // For exit()

#define ROT_SPEED 0.005 // A small value for a smooth rotation speed
#define MOVE_SPEED 0.008 // A small value for a smooth movement speed

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

// Loads a single XPM file into an t_img struct and returns 1 on failure
int load_texture(t_data *data, t_img *tex_img, char *path)
{
    tex_img->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr, path, &tex_img->width, &tex_img->height);
    if (!tex_img->img_ptr)
        return (1);
    tex_img->addr = mlx_get_data_addr(tex_img->img_ptr, &tex_img->bits_per_pixel, &tex_img->line_length, &tex_img->endian);
    return (0);
}

// Loads all textures and stores them in the data structure
int load_textures(t_data *data)
{
    // The order here matters. It corresponds to the index used later.
    if (load_texture(data, &data->textures[0], "./textures/wall_N.xpm")) return (1); // North wall (side == 1, stepY == -1)
    if (load_texture(data, &data->textures[1], "./textures/wall_S.xpm")) return (1); // South wall (side == 1, stepY == 1)
    if (load_texture(data, &data->textures[2], "./textures/wall_E.xpm")) return (1); // East wall (side == 0, stepX == 1)
    if (load_texture(data, &data->textures[3], "./textures/wall_W.xpm")) return (1); // West wall (side == 0, stepX == -1)
    return (0);
}


// The main raycasting and 3D rendering function
void raycast(t_data *data)
{
    for (int x = 0; x < WIN_W; x++)
    {
        double cameraX = 2 * x / (double)WIN_W - 1;
        double rayDirX = data->dirX + data->planeX * cameraX;
        double rayDirY = data->dirY + data->planeY * cameraX;

        int mapX = (int)data->posX;
        int mapY = (int)data->posY;

        double deltaDistX;
        double deltaDistY;
        if (rayDirX == 0) deltaDistX = 1e30;
        else deltaDistX = fabs(1 / rayDirX);
        if (rayDirY == 0) deltaDistY = 1e30;
        else deltaDistY = fabs(1 / rayDirY);

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
        int side; // 0 for X-axis hit, 1 for Y-axis hit
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
            if (mapX >= 0 && mapX < MAP_SIZE_W && mapY >= 0 && mapY < MAP_SIZE_H && data->worldMap[mapY][mapX] > 0)
                hit = 1;
        }

        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(WIN_H / perpWallDist);
        int drawStart = -lineHeight / 2 + WIN_H / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_H / 2;
        if (drawEnd >= WIN_H) drawEnd = WIN_H - 1;

        // --- TEXTURE MAPPING START ---

        // 1. Determine which texture to use
        int texNum;
        if (side == 0) { // X-axis hit (East or West wall)
            if (rayDirX > 0) texNum = 2; // East wall
            else texNum = 3; // West wall
        } else { // Y-axis hit (North or South wall)
            if (rayDirY > 0) texNum = 1; // South wall
            else texNum = 0; // North wall
        }

        // 2. Calculate the exact hit point on the wall
        double wallX;
        if (side == 0) wallX = data->posY + perpWallDist * rayDirY;
        else wallX = data->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX); // Subtracts the integer part to get the fractional part

        // 3. Calculate the x-coordinate on the texture
        int texX = (int)(wallX * (double)TEX_SIZE);
        if (side == 0 && rayDirX > 0) texX = TEX_SIZE - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEX_SIZE - texX - 1;

        // --- NEW TEXTURE MAPPING CALCULATION ---
        // We calculate a floating-point step for the texture Y-coordinate.
        double texStep = 1.0 * data->textures[texNum].height / lineHeight;
        // We also calculate the starting position for the texture based on the drawStart.
        double texPos = (drawStart - WIN_H / 2.0 + lineHeight / 2.0) * texStep;

        // 4. Draw the textured wall slice, pixel by pixel
        for (int y = drawStart; y < drawEnd; y++)
        {
            // The texture Y-coordinate is now a floating point value.
            int texY = (int)texPos;
            
            // Get the color from the texture's image buffer
            unsigned int color = *((unsigned int*)(data->textures[texNum].addr + (texY * data->textures[texNum].line_length + texX * (data->textures[texNum].bits_per_pixel / 8))));
            
            put_pixel_to_img(data, x, y, color);
            
            // Increment the texture position by our calculated step
            texPos += texStep;
        }

        // --- TEXTURE MAPPING END ---

        // Draw floor and ceiling
        for(int y = drawEnd; y < WIN_H; y++) put_pixel_to_img(data, x, y, 0x4B371C);
        for(int y = 0; y < drawStart; y++) put_pixel_to_img(data, x, y, 0x40c9b9);
    }
}

// Handles key press events, setting the rotation and movement state
int key_press(int keycode, t_data *data)
{
    if (keycode == 53) exit(0);
    if (keycode == 65361) data->is_rotating_left = 1;
    if (keycode == 65363) data->is_rotating_right = 1;
    if (keycode == 65362) data->is_moving_forward = 1;
    if (keycode == 65364) data->is_moving_backward = 1;
    return (0);
}

// Handles key release events, resetting the rotation and movement state
int key_release(int keycode, t_data *data)
{
    if (keycode == 65361) data->is_rotating_left = 0;
    if (keycode == 65363) data->is_rotating_right = 0;
    if (keycode == 65362) data->is_moving_forward = 0;
    if (keycode == 65364) data->is_moving_backward = 0;
    return (0);
}

// Handles window close event
int close_window(t_data *data)
{
    (void)data;
    exit(0);
    return (0);
}

// The main rendering loop function, called by mlx_loop_hook
int render(t_data *data)
{
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

    mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
    
    raycast(data);
    
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
    return (0);
}

int main(void)
{
    t_data data;

    int worldMap[12][24] = {
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

	int y = 0;
	while (y < MAP_SIZE_H)
	{
		int x = 0;
		while (x < MAP_SIZE_W)
		{
			data.worldMap[y][x] = worldMap[y][x];
			x++;
		}
		y++;
	}
    
    data.posX = 2.0; data.posY = 2.0;
    data.dirX = 1.0; data.dirY = 0.0;
    data.planeX = 0.0; data.planeY = 0.85;
    
    data.is_rotating_left = 0;
    data.is_rotating_right = 0;
    data.is_moving_forward = 0;
    data.is_moving_backward = 0;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL) return (1);
    
    // Call the new texture loading function
    if (load_textures(&data))
    {
        // Add cleanup code here if a texture fails to load
        return (1);
    }

    data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, "Cub3D - Raycaster");
    if (data.win_ptr == NULL) return (1);
    
    data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
    if (data.img.img_ptr == NULL) return (1);
    data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);

    mlx_loop_hook(data.mlx_ptr, &render, &data);
    
    mlx_hook(data.win_ptr, 2, 1L << 0, &key_press, &data);
    mlx_hook(data.win_ptr, 3, 1L << 1, &key_release, &data);
    
    mlx_hook(data.win_ptr, 17, 1L << 17, &close_window, &data);

    mlx_loop(data.mlx_ptr);

    return (0);
}

