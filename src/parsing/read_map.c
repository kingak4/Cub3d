#include "../../cub3d.h"

void	free_pars(t_pars *pars)
{
	if (!pars)
		return ;
	if (pars->n_wall)
		free(pars->n_wall);
	if (pars->s_wall)
		free(pars->s_wall);
	if (pars->e_wall)
		free(pars->e_wall);
	if (pars->w_wall)
		free(pars->w_wall);
}

void	clean_read(t_pars *data, int *count)
{
	int	i;

	i = 0;
	if (!data->n_wall || !data->s_wall || !data->e_wall
		|| !data->w_wall || data->floor == -1 || data->celling == -1)
	{
		write(2, "Error: missing texture or color\n", 33);
		free_pars(data);
		if (data->map)
		{
			while (i < *count)
			{
				free(data->map[i]);
				i++;
			}
			free(data->map);
		}
		exit(1);
	}
}

void	add_to_struct(char *line, int *found, t_pars *data)
{
	char	*copy;
	char	*trimmed;

	copy = ft_strdup(line);
	if (!copy)
		return ;
	trimmed = space(copy);
	free(copy);
	set_found_flag(trimmed, found);
	parse_line(trimmed, data);
	p_f_and_c(trimmed, data);
	free(trimmed);
}

static void	process_map_line(char *line, t_pars *data, int *count)
{
	char	*line_no_nl;
	size_t	len;

	line_no_nl = ft_strdup(line);
	if (!line_no_nl)
		return ;
	len = ft_strlen(line_no_nl);
	if (len > 0 && line_no_nl[len - 1] == '\n')
		line_no_nl[len - 1] = '\0';
	data->map = append_line(data->map, line_no_nl, *count);
	(*count)++;
	free(line_no_nl);
}

void	read_file(int fd, t_pars *data, int count, size_t len)
{
	char	*line;
	int		found[6];

	ft_memset(found, 0, sizeof(found));
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (*line == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_no(line) || is_so(line) || is_we(line)
			|| is_ea(line) || is_floor(line) || is_ceiling(line))
			add_to_struct(line, found, data);
		else
			process_map_line(line, data, &count);
		free(line);
		line = get_next_line(fd);
	}
	clean_read(data, &count);
}
