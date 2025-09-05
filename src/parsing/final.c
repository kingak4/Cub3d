#include "../../cub3d.h"

void	clean_map(t_pars *data)
{
	int i;

	i = 0;
	if (data->map)
	{
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	}
}

int	final(t_pars *data, t_vector2 *node)
{
	int i;
	
	i = 0;
	if (check_textures(data) && is_player(node, data)
		&& is_map_ok(data))
	{
		if (find_palyer(node, data,0 ,0) == 2)
		{
			free_pars(data);
			clean_map(data);
			return (0);
		}
		get_map_size(data);
		if (is_map(data))
			printf( "map ok\n");
		else
		{
			free_pars(data);
			clean_map(data);
			return (0);
		}
	}
	return (1);
}
