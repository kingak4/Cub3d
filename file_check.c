/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:29 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/02 12:52:03 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (0);
	while (i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return (1);
	return (0);
}

int	check_prefix(char *line, char *prefix)
{
	size_t	i;

	i = 0;
	while (prefix[i] && line[i] && prefix[i] == line[i])
		i++;
	if (prefix[i] == '\0')
		return (1);
	return (0);
}

char	**append_line(char **lines, char *new_line, int count)
{
	char	**new_tab;
	int		i;

	new_tab = malloc(sizeof(char *) * (count + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_tab[i] = lines[i];
		i++;
	}
	new_tab[i] = ft_strdup(new_line);
	new_tab[i + 1] = NULL;
	free(lines);
	return (new_tab);
}

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
	return (map);
}
