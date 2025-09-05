#include "../../cub3d.h"

int	check_f(char *path)
{
	int		fd;
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strcmp(path + len - 4, ".xpm", 4) == 0)
	{
		write(2, "Error: wrong file extension for texture file\n", 45);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: texture file does not exist\n", 36);
		return (0);
	}
	close(fd);
	return (1);
}

int	check_textures(t_pars *data)
{
	if (!check_f(data->n_wall))
		return (0);
	if (!check_f(data->s_wall))
		return (0);
	if (!check_f(data->e_wall))
		return (0);
	if (!check_f(data->w_wall))
		return (0);
	return (1);
}
