/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_one_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:01:43 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/03 10:01:56 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static size_t	skip_start(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}

static int	skip_end(const char *s)
{
	int	i;

	i = (int)ft_strlen(s) - 1;
	while (i >= 0 && is_space(s[i]))
		i--;
	return (i);
}

static void	copy_trimmed(const char *s, int start, int end, char *dest)
{
	int	i;
	int	j;

	j = 0;
	i = start;
	while (i <= end)
	{
		if (is_space(s[i]))
		{
			if (j > 0 && dest[j - 1] != ' ')
				dest[j++] = ' ';
		}
		else
			dest[j++] = s[i];
		i++;
	}
	dest[j] = '\0';
}

char	*space(const char *s)
{
	size_t	start;
	int		end;
	char	*result;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
		return (ft_strdup(""));
	start = skip_start(s);
	end = skip_end(s);
	if (end < (int)start)
	{
		result = malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
	result = malloc((end - (int)start + 2) * sizeof(char));
	if (!result)
		return (NULL);
	copy_trimmed(s, start, end, result);
	return (result);
}
