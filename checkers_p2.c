/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_p2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:30:34 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/02 12:50:46 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ceiling(char *line)
{
	return (check_prefix(line, "C "));
}

void	set_found_flag(char *line, int *found)
{
	if (is_no(line))
		found[0] = 1;
	else if (is_so(line))
		found[1] = 1;
	else if (is_we(line))
		found[2] = 1;
	else if (is_ea(line))
		found[3] = 1;
	else if (is_floor(line))
		found[4] = 1;
	else if (is_ceiling(line))
		found[5] = 1;
}

int	all_headers_found(int *found)
{
	return (found[0] && found[1] && found[2]
		&& found[3] && found[4] && found[5]);
}

int	check_file(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len < 5)
		return (0);
	if (ft_strcmp(s + len - 4, ".cub", 4))
		return (1);
	write(1, "wrong map file\n", 15);
	return (0);
}

void	p_f_and_c(char *line, t_pars *data)
{
	char	*value;
	
	if (check_prefix(line, "F "))
	{
		value = line + 2;
		data->floor = pars_color(value);
	}
	else if (check_prefix(line, "C "))
	{
		value = line + 2;
		data->celling = pars_color(value);
	}
}
