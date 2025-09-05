#include "../../cub3d.h"
#include <stdio.h>

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		clean_exit(data);
	if (keycode == 65361)
		data->is_rotating_left = 1;
	if (keycode == 65363)
		data->is_rotating_right = 1;
	if (keycode == 65362 || keycode == 119)
		data->is_moving_forward = 1;
	if (keycode == 65364 || keycode == 115)
		data->is_moving_backward = 1;
	if (keycode == 97)
		data->is_moving_left = 1;
	if (keycode == 100)
		data->is_moving_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 65307)
		clean_exit(data);
	if (keycode == 65361)
		data->is_rotating_left = 0;
	if (keycode == 65363)
		data->is_rotating_right = 0;
	if (keycode == 65362 || keycode == 119)
		data->is_moving_forward = 0;
	if (keycode == 65364 || keycode == 115)
		data->is_moving_backward = 0;
	if (keycode == 97)
		data->is_moving_left = 0;
	if (keycode == 100)
		data->is_moving_right = 0;
	return (0);
}
