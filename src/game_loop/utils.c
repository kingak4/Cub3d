/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:25:05 by korzecho          #+#    #+#             */
/*   Updated: 2025/09/10 12:25:06 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init_data(t_data *data, t_pars *map_data)
{
	data->map_data = map_data;
	data->pos_x = map_data->node->x + 0.5;
	data->pos_y = map_data->node->y + 0.5;
	set_player_dir(data);
	data->is_rotating_left = 0;
	data->is_rotating_right = 0;
	data->is_moving_forward = 0;
	data->is_moving_backward = 0;
	data->is_moving_right = 0;
	data->is_moving_left = 0;
	data->cant_move_forward = 0;
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
	if (load_texture(data, &data->textures[0], data->map_data->n_wall))
		return (1);
	if (load_texture(data, &data->textures[1], data->map_data->s_wall))
		return (1);
	if (load_texture(data, &data->textures[2], data->map_data->e_wall))
		return (1);
	if (load_texture(data, &data->textures[3], data->map_data->w_wall))
		return (1);
	return (0);
}

void	draw_floor_ceiling(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_end;
	while (y < WIN_H)
	{
		put_pixel_to_img(data, x, y, data->map_data->floor);
		y++;
	}
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_img(data, x, y, data->map_data->celling);
		y++;
	}
}
