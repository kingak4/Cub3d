#include "cub3d.h"

static void	set_ray_props(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)WIN_W - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	on_dda_hit(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= 0 && ray->map_x < MAP_SIZE_W
			&& ray->map_y >= 0 && ray->map_y < MAP_SIZE_H
			&& data->world_map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
}

static void	dda_algo(t_ray *ray, t_data *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_dist_y;
	}

	on_dda_hit(ray, data);
	/*
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= 0 && ray->map_x < MAP_SIZE_W
			&& ray->map_y >= 0 && ray->map_y < MAP_SIZE_H
			&& data->world_map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
	*/
}

static void	draw_wall_slice(t_data *data, t_ray *ray, int x)
{
	double			wall_x;
	int				tex_x;
	double			tex_step;
	double			tex_pos;
	int				y;
	int				tex_y;
	unsigned int	color;

	if (ray->side == 0)
		wall_x = data->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_SIZE);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = TEX_SIZE - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = TEX_SIZE - tex_x - 1;
	tex_step = 1.0 * data->textures[ray->tex_num].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2.0 + ray->line_height / 2.0)
		* tex_step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		color = *((unsigned int *)(data->textures[ray->tex_num].addr
					+ (tex_y * data->textures[ray->tex_num].line_length
						+ tex_x * (data->textures[ray->tex_num].bits_per_pixel
							/ 8))));
		put_pixel_to_img(data, x, y, color);
		tex_pos += tex_step;
		y++;
	}
}

void	raycast(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_W)
	{
		set_ray_props(&ray, data, x);
		ray.hit = 0;
		dda_algo(&ray, data);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		ray.line_height = (int)(WIN_H / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + WIN_H / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WIN_H / 2;
		if (ray.draw_end >= WIN_H)
			ray.draw_end = WIN_H - 1;
		if (ray.side == 0)
		{
			if (ray.ray_dir_x > 0)
				ray.tex_num = 2;
			else
				ray.tex_num = 3;
		}
		else
		{
			if (ray.ray_dir_y > 0)
				ray.tex_num = 1;
			else
				ray.tex_num = 0;
		}
		draw_wall_slice(data, &ray, x);
		draw_floor_ceiling(data, &ray, x);
		x++;
	}
}
