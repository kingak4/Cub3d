#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define WIN_W 1000
# define WIN_H 600
# define TEX_SIZE 128
# define ROT_SPEED 0.005
# define MOVE_SPEED 0.008

typedef struct s_pars
{
	char				*n_wall;
	char				*s_wall;
	char				*e_wall;
	char				*w_wall;
	int					floor;
	int					celling;
	char				**map;
	int					w;
	int					h;
	struct s_vector2	*node;
	char				player_dir_char;
}	t_pars;

// where is player
typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

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
	char	**world_map;
	int		is_rotating_left;
	int		is_rotating_right;
	int		is_moving_forward;
	int		is_moving_backward;
	int		is_moving_right;
	int		is_moving_left;
	t_img	textures[4];
	t_pars	*map_data;
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

// Raycasting
int		main_raycaster(t_pars *map_data);
void	raycast(t_data *data);

//Init
void	set_player_dir(t_data *data);
void	ft_init_data(t_data *data, t_pars *map_data);
int		load_texture(t_data *data, t_img *tex_img, char *path);
int		load_textures(t_data *data);

//Hooks
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		close_window(t_data *data);
void	clean_exit(t_data *data);

//Rotation and movement
void	rotate_right(t_data *data);
void	rotate_left(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);

//Rendering
void	draw_wall_slice(t_data *data, t_ray *ray, int x);
void	put_pixel_to_img(t_data *data, int x, int y, int color);
void	draw_floor_ceiling(t_data *data, t_ray *ray, int x);

// parsing and reading map file
int		check_file(char *s); // is file correct
char	*space(const char *s); // make on space
int		check_prefix(char *line, char *prefix);
void	read_file(int fd, t_pars *data, int count, size_t len);
void	parse_line(char *line, t_pars *data);
void	p_f_and_c(char *line, t_pars *data);
int		pars_color(char *line);
void	init_pars(t_pars *data, t_vector2 *node);
int		ft_strcmp(char *s1, char *s2, size_t n);
char	**append_line(char **lines, char *new_line, int count);

//small checker for walls 
int		is_no(char *line);
int		is_so(char *line);
int		is_we(char *line);
int		is_ea(char *line);
int		is_floor(char *line);
int		is_ceiling(char *line);

// flag for checkers
void	set_found_flag(char *line, int *found); // setting flags
int		all_headers_found(int *found); // finnal check for flags

// clean code
void	free_tab(char **splited);
void	free_pars(t_pars *pars);
void	clean_map(t_pars *data);
// palyer && map checking 
int	find_palyer(t_vector2 *node, t_pars *data, int x, int y);
int		is_player(t_vector2 *node, t_pars *data);
int		map_check(t_pars *data);
int		is_map_ok(t_pars *data);
void	get_map_size(t_pars *data);

// checking texture 
int		check_f(char *path);
int		check_textures(t_pars *data);

// cheking edges of teh map 
int	first(t_pars *data);
int	last(t_pars *data);
int	check_holes(t_pars *data);
int	is_map(t_pars *data);

int	final(t_pars *data, t_vector2 *node);

#endif
