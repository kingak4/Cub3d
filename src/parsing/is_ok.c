/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ok.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:29:00 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/05 13:53:53 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_no(char *line)
{
	return (check_prefix(line, "NO "));
}

int	is_so(char *line)
{
	return (check_prefix(line, "SO "));
}

int	is_we(char *line)
{
	return (check_prefix(line, "WE "));
}

int	is_ea(char *line)
{
	return (check_prefix(line, "EA "));
}

int	is_floor(char *line)
{
	return (check_prefix(line, "F "));
}
