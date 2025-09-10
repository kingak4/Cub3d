/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:25:13 by korzecho          #+#    #+#             */
/*   Updated: 2025/09/10 12:25:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_tex_params	calculate_texture_params(t_data *data, t_ray *ray)
{
	t_tex_params	params;
	double			wall_x;

	if (ray->side == 0)
		wall_x = data->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	params.tex_x = (int)(wall_x * (double)TEX_SIZE);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		params.tex_x = TEX_SIZE - params.tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		params.tex_x = TEX_SIZE - params.tex_x - 1;
	params.tex_step = 1.0 * data->textures[ray->tex_num].height
		/ ray->line_height;
	params.tex_pos = (ray->draw_start - WIN_H / 2.0 + ray->line_height / 2.0)
		* params.tex_step;
	return (params);
}

static void	render_wall_column(t_data *data, t_ray *ray,
		int x, t_tex_params params)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)params.tex_pos;
		color = *((unsigned int *)(data->textures[ray->tex_num].addr
					+ (tex_y * data->textures[ray->tex_num].line_length
						+ params.tex_x
						*(data->textures[ray->tex_num].bits_per_pixel / 8))));
		put_pixel_to_img(data, x, y, color);
		params.tex_pos += params.tex_step;
		y++;
	}
}

void	draw_wall_slice(t_data *data, t_ray *ray, int x)
{
	t_tex_params	params;

	params = calculate_texture_params(data, ray);
	render_wall_column(data, ray, x, params);
}
