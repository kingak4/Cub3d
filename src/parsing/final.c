/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:src/parsing/wall_check.c
/*   Created: 2025/09/04 13:30:03 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/05 13:53:53 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
========
/*   Created: 2025/09/05 13:49:01 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/05 15:03:50 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	clean_map(t_pars *data)
{
	int i;

	i = 0;
	if (data->map)
	{
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	}
}

int	final(t_pars *data, t_vector2 *node)
{
	int i;
	
	i = 0;
	if (check_textures(data) && is_player(node, data)
		&& is_map_ok(data))
	{
		if (find_palyer(node, data,0 ,0) == 0)
		{
			free_pars(data);
			clean_map(data);
			return (0);
		}
		get_map_size(data);
		if (is_map(data))
			printf( "map ok\n");
	}
	return (1);
}
>>>>>>>> origin/kinga_branch:src/parsing/final.c
