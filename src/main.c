#include "../cub3d.h"

int	render(t_data *data)
{
	rotate_right(data);
	rotate_left(data);
	move_forward(data);
	move_backward(data);
	mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img_ptr, 0, 0);
	return (0);
}

void	clean_exit(t_data *data)
{
	int	i;

	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	i = 0;
	while (i < 4)
	{
		if (data->textures[i].img_ptr)
			mlx_destroy_image(data->mlx_ptr, data->textures[i].img_ptr);
		i++;
	}
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}

int	close_window(t_data *data)
{
	clean_exit(data);
	return (0);
}

int	main_raycaster(t_pars *map_data)
{
	t_data	data;

	ft_init_data(&data, map_data);
	ft_init_map(&data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	if (load_textures(&data))
		clean_exit(&data);
	data.win_ptr = mlx_new_window(data.mlx_ptr,
			WIN_W, WIN_H, "Cub3D - Raycaster");
	if (data.win_ptr == NULL)
		clean_exit(&data);
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIN_W, WIN_H);
	if (data.img.img_ptr == NULL)
		clean_exit(&data);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr,
			&data.img.bits_per_pixel,
			&data.img.line_length, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, 2, 1L << 0, &key_press, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, &key_release, &data);
	mlx_hook(data.win_ptr, 17, 1L << 17, &close_window, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
