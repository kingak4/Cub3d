/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:41:21 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/05 13:47:37 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_hole(t_pars *data, int y, int x)
{
	char	up;
	char	down;
	char	left;
	char	right;

	if (y > 0 && x < (int)ft_strlen(data->map[y - 1]))
		up = data->map[y - 1][x];
	else
		up = '1';
	if (y < data->h - 1 && x < (int)ft_strlen(data->map[y + 1]))
		down = data->map[y + 1][x];
	else
		down = '1';
	if (x > 0)
		left = data->map[y][x - 1];
	else
		left = '1';
	if (x < (int)ft_strlen(data->map[y]) - 1)
		right = data->map[y][x + 1];
	else
		right = '1';
	if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
		return (1);
	return (0);
}

int	check_holes(t_pars *data)
{
	int	y;
	int	x;

	y = 1;
	while (y < data->h - 1)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == '0')
			{
				if (is_hole(data, y, x))
				{
					printf("Map hole detected near (%d, %d)\n", y, x);
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}
