/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:25:16 by korzecho          #+#    #+#             */
/*   Updated: 2025/09/10 12:25:17 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_north(t_data *data)
{
	data->dir_x = 0.0;
	data->dir_y = -1.0;
	data->plane_x = 0.85;
	data->plane_y = 0;
}

void	set_south(t_data *data)
{
	data->dir_x = 0.0;
	data->dir_y = 1.0;
	data->plane_x = -0.85;
	data->plane_y = 0;
}

void	set_east(t_data *data)
{
	data->dir_x = 1.0;
	data->dir_y = 0.0;
	data->plane_x = 0;
	data->plane_y = 0.85;
}

void	set_west(t_data *data)
{
	data->dir_x = -1.0;
	data->dir_y = 0.0;
	data->plane_x = 0;
	data->plane_y = -0.85;
}

void	set_player_dir(t_data *data)
{
	char	c;

	c = data->map_data->player_dir_char;
	if (c == 'N')
		set_north(data);
	else if (c == 'S')
		set_south(data);
	else if (c == 'E')
		set_east(data);
	else if (c == 'W')
		set_west(data);
}
