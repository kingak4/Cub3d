#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		clean_exit(data);
	if (keycode == 65361)
		data->is_rotating_left = 1;
	if (keycode == 65363)
		data->is_rotating_right = 1;
	if (keycode == 65362)
		data->is_moving_forward = 1;
	if (keycode == 65364)
		data->is_moving_backward = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 53)
		clean_exit(data);
	if (keycode == 65361)
		data->is_rotating_left = 0;
	if (keycode == 65363)
		data->is_rotating_right = 0;
	if (keycode == 65362)
		data->is_moving_forward = 0;
	if (keycode == 65364)
		data->is_moving_backward = 0;
	return (0);
}
