/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:30:00 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/17 09:35:44 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	main(int argc, char **argv)
{
	t_pars		data;
	t_vector2	node;
	int			fd;
	char		*map;

	if (argc != 2)
		return (write(1, "Too few args\n", 13), 1);
	if (argv[1] == NULL)
		return (1);
	map = argv[1];
	if (check_file(map) == 0)
		return (1);
	init_pars(&data, &node);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "Error: cannot open file\n", 24), 1);
	read_file(fd, &data, 0, 0);
	close(fd);
	if (!final(&data, &node))
		return (1);
	data.node = &node;
	main_raycaster(&data);
	free_pars(&data);
	clean_map(&data);
	return (0);
}
