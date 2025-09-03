#include "../cub3d.h"

void	ft_init_data(t_data *data)
{
	data->pos_x = 2.0;
	data->pos_y = 2.0;
	data->dir_x = 1.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.85;
	data->is_rotating_left = 0;
	data->is_rotating_right = 0;
	data->is_moving_forward = 0;
	data->is_moving_backward = 0;
}

void	put_pixel_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = data->img.addr + (y * data->img.line_length + x
				* (data->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	load_texture(t_data *data, t_img *tex_img, char *path)
{
	tex_img->img_ptr = mlx_xpm_file_to_image
		(data->mlx_ptr, path, &tex_img->width, &tex_img->height);
	if (!tex_img->img_ptr)
		return (1);
	tex_img->addr = mlx_get_data_addr
		(tex_img->img_ptr, &tex_img->bits_per_pixel,
			&tex_img->line_length, &tex_img->endian);
	return (0);
}

int	load_textures(t_data *data)
{
	if (load_texture(data, &data->textures[0], "./textures/wall_N.xpm"))
		return (1);
	if (load_texture(data, &data->textures[1], "./textures/wall_S.xpm"))
		return (1);
	if (load_texture(data, &data->textures[2], "./textures/wall_E.xpm"))
		return (1);
	if (load_texture(data, &data->textures[3], "./textures/wall_W.xpm"))
		return (1);
	return (0);
}

void	draw_floor_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < WIN_H)
	{
		put_pixel_to_img(data, x, y, 0x4B371C);
		y++;
	}
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_img(data, x, y, 0x40c9b9);
		y++;
	}
}

void	ft_init_map(t_data *data)
{
	int		x;
	int		y;
	int		world_map[12][24] = {
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

	y = 0;
	while (y < MAP_SIZE_H)
	{
		x = 0;
		while (x < MAP_SIZE_W)
		{
			data->world_map[y][x] = world_map[y][x];
			x++;
		}
		y++;
	}
}
