/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:47:15 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/05 12:18:35 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	find_palyer(t_vector2 *node, t_pars *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'E'
				|| data->map[y][x] == 'S'|| data->map[y][x] == 'W')
			{
				node->x = x;
				node->y = y;
				data->player_dir_char = data->map[y][x];
				data->map[y][x] = '0';
				return (1);
			}
			x++;
		}
		y++;
	}
	printf("player x: %d, y: %d\n", node->x, node->y);
	return (0);
}

int	is_player(t_vector2 *node, t_pars *data)
{
	if (find_palyer(node, data) == 0)
	{
		write(2, "Error: no player on the map\n", 28);
		return (0);
	}
	return (1);
}

int	map_check(t_pars *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1' || data->map[y][x] == '0'
				|| data->map[y][x] == ' ' || data->map[y][x] == '\n'
				|| data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				x++;
				continue;
			}
			else
				return (0);
		}
		y++;
	}
	return (1);
}

int	is_map_ok(t_pars *data)
{
	if (map_check(data) == 0)
	{
		write(2, "Error: wrong map\n", 17);
		return (0);
	}
	return (1);
}
void	get_map_size(t_pars *data)
{
	int	y;
	int	x_end;
	int	x_start;
	int	line_width;

	y = 0;
	data->w = 0;
	while (data->map[y])
	{
		x_start = 0;
		x_end = 0;
		while (data->map[y][x_end] != '\0')
			x_end++;
		x_end--; 
		while (x_end >= x_start && data->map[y][x_end] == ' ')
			x_end--;
		line_width = x_end - x_start + 1;
		if (line_width > data->w)
			data->w = line_width;
		y++;
	}
	data->h = y;
}
