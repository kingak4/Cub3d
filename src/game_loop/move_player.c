#include "../../cub3d.h"

void	move_forward(t_data *data)
{
	if (data->is_moving_forward && !data->cant_move_forward)
	{
		if (data->world_map[(int)(data->pos_y + data->dir_y
				* MOVE_SPEED)][(int)(data->pos_x)] == '0')
			data->pos_y += data->dir_y * MOVE_SPEED;
		if (data->world_map[(int)(data->pos_y)][(int)(data->pos_x
				+ data->dir_x * MOVE_SPEED)] == '0')
			data->pos_x += data->dir_x * MOVE_SPEED;
	}
}

void	move_backward(t_data *data)
{
	if (data->is_moving_backward)
	{
		if (data->world_map[(int)(data->pos_y - data->dir_y
				* MOVE_SPEED)][(int)(data->pos_x)] == '0')
			data->pos_y -= data->dir_y * MOVE_SPEED;
		if (data->world_map[(int)(data->pos_y)][(int)
			(data->pos_x - data->dir_x * MOVE_SPEED)] == '0')
			data->pos_x -= data->dir_x * MOVE_SPEED;
	}
}

void	move_right(t_data *data)
{
	if (data->is_moving_right)
	{
		if (data->world_map[(int)(data->pos_y)]
			[(int)(data->pos_x + data->plane_x * MOVE_SPEED)] == '0')
			data->pos_x += data->plane_x * MOVE_SPEED;
		if (data->world_map[(int)(data->pos_y + data->plane_y
				* MOVE_SPEED)][(int)(data->pos_x)] == '0')
			data->pos_y += data->plane_y * MOVE_SPEED;
	}
}

void	move_left(t_data *data)
{
	if (data->is_moving_left)
	{
		if (data->world_map[(int)(data->pos_y)]
			[(int)(data->pos_x - data->plane_x * MOVE_SPEED)] == '0')
			data->pos_x -= data->plane_x * MOVE_SPEED;
		if (data->world_map[(int)(data->pos_y - data->plane_y
				* MOVE_SPEED)][(int)(data->pos_x)] == '0')
			data->pos_y -= data->plane_y * MOVE_SPEED;
	}
}
