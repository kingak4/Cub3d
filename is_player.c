/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:47:15 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/04 12:57:54 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				return (1);
			}
			x++;
		}
		y++;
	}
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