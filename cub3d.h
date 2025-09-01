/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:34:34 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/01 17:26:49 by kikwasni         ###   ########.fr       */
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

int		check_file(char *s);
char	*space(const char *s);
char	**read_file(int fd, t_pars *data);
void parse_line(char *line, t_pars *data);
int check_prefix(char *line, char *prefix);

#endif
