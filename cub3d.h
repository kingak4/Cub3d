/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:34:34 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/03 09:51:28 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>

typedef struct s_pars
{
	char	*n_wall;
	char	*s_wall;
	char	*e_wall;
	char	*w_wall;
	int		floor;
	int		celling;
}	t_pars;

// checkers for files
int		check_file(char *s); // is file correct
char	*space(const char *s); // make on space and delite spaces in start and the end
int		check_prefix(char *line, char *prefix);
char	**read_file(int fd, t_pars *data);
void	parse_line(char *line, t_pars *data);
void	p_f_and_c(char *line, t_pars *data);
int		pars_color(char *line);
void	free_tab(char **splited);
void	init_pars(t_pars *data);
int		ft_strcmp(char *s1, char *s2, size_t n);
char	**append_line(char **lines, char *new_line, int count);

//small checker for walls 
int		is_no(char *line);
int		is_so(char *line);
int		is_we(char *line);
int		is_ea(char *line);
int		is_floor(char *line);
int		is_ceiling(char *line);

void	set_found_flag(char *line, int *found); // setting flags
int		all_headers_found(int *found); // finnal check for flags

#endif
