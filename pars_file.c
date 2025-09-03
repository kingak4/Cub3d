/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:33:45 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/03 11:51:50 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_pars(t_pars *data)
{
	data->n_wall = NULL;
	data->s_wall = NULL;
	data->e_wall = NULL;
	data->w_wall = NULL;
	data->floor = -1;
	data->celling = -1;
	data->map = NULL;
}

void	parse_line(char *line, t_pars *data)
{
	char	*value;

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
}

void	free_tab(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

int	pars_color(char *line)
{
	char	**token;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	token = ft_split(line, ',');
	if (!token || !token[0] || !token[1] || !token[2])
		return (-1);
	r = ft_atoi(token[0]);
	g = ft_atoi(token[1]);
	b = ft_atoi(token[2]);
	free_tab(token);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return (r * 256 * 256 + g * 256 + b);
}
