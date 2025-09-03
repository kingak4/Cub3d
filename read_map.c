/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 09:01:28 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/03 09:51:57 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_file(int fd, t_pars *data)
{
	char	*line; // need to make good copy of the map ande dele leaks
	char	**map = NULL;
	int		count = 0;
	int		found[6] = {0};

	while ((line = get_next_line(fd)))
	{
		char *trimmed = space(line);
		free(line);
		if (*trimmed == '\0')
		{
			free(trimmed);
			continue;
		}
		if (is_no(trimmed) || is_so(trimmed) || is_we(trimmed) ||
			is_ea(trimmed) || is_floor(trimmed) || is_ceiling(trimmed))
		{
			set_found_flag(trimmed, found);
			parse_line(trimmed, data);
			p_f_and_c(trimmed, data);
		}
		else
		{
			map = append_line(map, trimmed, count);
			count++;
		}
		free(trimmed);
	}
	if (!data->n_wall || !data->s_wall || !data->e_wall || !data->w_wall
		|| data->floor == -1 || data->celling == -1)
	{
		write(2, "Error: missing texture or color\n", 33);
		exit(1);
	}
	return (map);
}