
#include "../../cub3d.h"

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
