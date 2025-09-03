#include "../cub3d.h"

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

void	move_forward(t_data *data)
{
	if (data->is_moving_forward)
	{
		if (data->world_map[(int)(data->pos_y + data->dir_y
				* MOVE_SPEED)][(int)(data->pos_x)] == 0)
			data->pos_y += data->dir_y * MOVE_SPEED;
		if (data->world_map[(int)(data->pos_y)][(int)(data->pos_x
				+ data->dir_x * MOVE_SPEED)] == 0)
			data->pos_x += data->dir_x * MOVE_SPEED;
	}
}

void	move_backward(t_data *data)
{
	if (data->is_moving_backward)
	{
		if (data->world_map[(int)(data->pos_y - data->dir_y
				* MOVE_SPEED)][(int)(data->pos_x)] == 0)
			data->pos_y -= data->dir_y * MOVE_SPEED;
		if (data->world_map[(int)(data->pos_y)][(int)
			(data->pos_x - data->dir_x * MOVE_SPEED)] == 0)
			data->pos_x -= data->dir_x * MOVE_SPEED;
	}
}
