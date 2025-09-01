/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:14:29 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/01 17:25:01 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int ft_strcmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1)
		return (0);
	while (i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return (1);
	return (0);
}

int check_file(char *s)
{
	size_t len;

	len = ft_strlen(s);
	if (len < 4)
		return (0);
	if (ft_strcmp(s + len - 4, ".cub", 4))
		return (1);
	write(1, "wrong map file\n", 15);
	return (0);
}

int check_prefix(char *line, char *prefix)
{
	size_t i;

	i = 0;
	while (prefix[i] && line[i] && prefix[i] == line[i])
		i++;
	if (prefix[i] == '\0')
		return (1);
	return (0);
}

int checker_first(char *line)
{
	int found[6];

	ft_bzero(found, sizeof(found));
	if (check_prefix(line, "NO "))
		found[0] = 1;
	else if (check_prefix(line, "SO "))
		found[1] = 1;
	else if (check_prefix(line, "WE "))
		found[2] = 1;
	else if (check_prefix(line, "EA "))
		found[3] = 1;
	else if (check_prefix(line, "F"))
		found[4] = 1;
	else if (check_prefix(line, "C"))
		found[5] = 1;
	if (found[0] && found[1] && found[2] && found[3] && found[4] && found[5])
		return (1);
	write(1, "wrong map \n", 11);
	return (0);
}

char **append_line(char **lines, char *new_line, int count)
{
	char **new_tab;
	int i;

	new_tab = malloc(sizeof(char *) * (count + 2));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_tab[i] = lines[i];
		i++;
	}
	new_tab[i] = new_line;
	new_tab[i + 1] = NULL;
	free(lines);
	return (new_tab);
}
char **read_file(int fd, t_pars *data)
{
	char *line;
	char **map;
	int count;

	count = 0;
	map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue;
		}
		if (checker_first(line))
			parse_line(line, data);
		else
		{
			map = append_line(map, line, count);
			count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}
