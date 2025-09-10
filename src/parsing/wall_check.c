/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:30:18 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/10 12:30:19 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	first(t_pars *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (!data->map)
		return (0);
	while (data->map[0][x] != '\0')
	{
		if (data->map[0][x] != '1' && data->map[0][x] != ' ')
		{
			printf("The top side of the map is not filled with walls\n");
			return (0);
		}
		x++;
	}
	return (1);
}

int	last(t_pars *data)
{
	int	y;
	int	x;

	y = data->h - 1;
	x = 0;
	if (!data->map || data->h == 0)
		return (0);
	while (data->map[y][x] != '\0')
	{
		if (data->map[y][x] != '1' && data->map[y][x] != ' ')
		{
			printf("The bottom side of the map is not filled with walls\n");
			return (0);
		}
		x++;
	}
	return (1);
}

int	check_sides(t_pars *data)
{
	int	y;
	int	len;

	y = 1;
	while (y < data->h - 1)
	{
		if (data->map[y][0] != '1' && data->map[y][0] != ' ')
		{
			printf("Left side map is not filled with walls (line %d)\n", y);
			return (0);
		}
		len = ft_strlen(data->map[y]) - 1;
		if (len >= 0 && data->map[y][len] != '1' && data->map[y][len] != ' ')
		{
			printf("Right side  map is not filled with walls (line %d)\n", y);
			return (0);
		}
		y++;
	}
	return (1);
}

int	is_map(t_pars *data)
{
	if (!data->map || data->h == 0)
	{
		printf("Map is empty\n");
		return (0);
	}
	if (!first(data) || !last(data))
		return (0);
	if (!check_sides(data))
		return (0);
	if (!check_holes(data))
		return (0);
	return (1);
}
