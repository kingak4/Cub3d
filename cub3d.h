#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <math.h>
# include <stdlib.h>

# define WIN_W 1000
# define WIN_H 600
# define MAP_SIZE_W 24
# define MAP_SIZE_H 12
# define TEX_SIZE 128
# define ROT_SPEED 0.005
# define MOVE_SPEED 0.008

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		world_map[MAP_SIZE_H][MAP_SIZE_W];
	int		is_rotating_left;
	int		is_rotating_right;
	int		is_moving_forward;
	int		is_moving_backward;
	t_img	textures[4];
}	t_data;

typedef struct s_tex_params
{
	double	tex_step;
	double	tex_pos;
	int		tex_x;
}	t_tex_params;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
}	t_ray;

// Functions
void	put_pixel_to_img(t_data *data, int x, int y, int color);
int		load_texture(t_data *data, t_img *tex_img, char *path);
int		load_textures(t_data *data);
void	draw_floor_ceiling(t_data *data, t_ray *ray, int x);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		close_window(t_data *data);
void	clean_exit(t_data *data);
void	raycast(t_data *data);
void	ft_init_data(t_data *data);
void	ft_init_map(t_data *data);
//Rotation and movement
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
//Wall rendering
void	draw_wall_slice(t_data *data, t_ray *ray, int x);
#endif
