/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:25:07 by korzecho          #+#    #+#             */
/*   Updated: 2025/09/10 12:25:08 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	ray->hit = 0;
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
		if (ray->map_x >= 0 && ray->map_x < data->map_data->w
			&& ray->map_y >= 0 && ray->map_y < data->map_data->h)
		{
			if (data->world_map[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		else
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
}

void	set_texture_number(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 2;
		else
			ray->tex_num = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
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
		perp_wall_dis(&ray, data);
		ray.line_height = (int)(WIN_H / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + WIN_H / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + WIN_H / 2;
		if (ray.draw_end >= WIN_H)
			ray.draw_end = WIN_H - 1;
		set_texture_number(&ray);
		draw_wall_slice(data, &ray, x);
		draw_floor_ceiling(data, &ray, x);
		x++;
	}
}
