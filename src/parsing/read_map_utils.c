/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:53:22 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/17 10:53:24 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_map_part(char *line, t_pars *data, int *found, int *count)
{
	if (is_no(line) || is_so(line) || is_we(line)
		|| is_ea(line) || is_floor(line) || is_ceiling(line))
		add_to_struct(line, found, data);
	else
	{
		process_map_line(line, data, count);
		return (1);
	}
	return (0);
}
