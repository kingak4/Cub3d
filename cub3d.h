/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:34:34 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/05 10:56:08 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>

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
} t_vector2;

// parsing and reading map file
int		check_file(char *s); // is file correct
char	*space(const char *s); // make on space
int		check_prefix(char *line, char *prefix);
void	read_file(int fd, t_pars *data); // reading file
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
// palyer && map checking 
int		find_palyer(t_vector2 *node, t_pars *data);
int		is_player(t_vector2 *node, t_pars *data);
int		map_check(t_pars *data);
int		is_map_ok(t_pars *data);
void	get_map_size(t_pars *data);

// checking texture 
int		check_f(char *path);
int		check_textures(t_pars *data);

#endif
