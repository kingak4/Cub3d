#include "../../cub3d.h"

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->is_rotating_left)
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-ROT_SPEED)
			- data->dir_y * sin(-ROT_SPEED);
		data->dir_y = old_dir_x * sin(-ROT_SPEED)
			+ data->dir_y * cos(-ROT_SPEED);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROT_SPEED)
			- data->plane_y * sin(-ROT_SPEED);
		data->plane_y = old_plane_x * sin(-ROT_SPEED)
			+ data->plane_y * cos(-ROT_SPEED);
	}
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (data->is_rotating_right)
	{
		old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(ROT_SPEED)
			- data->dir_y * sin(ROT_SPEED);
		data->dir_y = old_dir_x * sin(ROT_SPEED)
			+ data->dir_y * cos(ROT_SPEED);
		old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(ROT_SPEED)
			- data->plane_y * sin(ROT_SPEED);
		data->plane_y = old_plane_x * sin(ROT_SPEED)
			+ data->plane_y * cos(ROT_SPEED);
	}
}
