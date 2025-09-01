/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:33:45 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/01 17:32:52 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_line(char *line, t_pars *data)
{
	char *value;

	if (check_prefix(line, "NO "))
	{
		value = line + 3;
		data->n_wall = ft_strdup(value);
	}
	else if (check_prefix(line, "SO "))
	{
		value = line + 3;
		data->s_wall = ft_strdup(value);
	}
	else if (check_prefix(line, "WE "))
	{
		value = line + 3;
		data->w_wall = ft_strdup(value);
	}
	else if (check_prefix(line, "EA "))
	{
		value = line + 3;
		data->e_wall = ft_strdup(value);
	}
	else if (check_prefix(line, "F "))
	{
		value = line + 2;
		data->floor = parse_color(value);
	}
	else if (check_prefix(line, "C "))
	{
		value = line + 2;
		data->celling = parse_color(value);
	}
}
