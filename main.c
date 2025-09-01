/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:50:22 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/01 17:29:07 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int ac, char *av[])
{
	char	*map;
	int		fd;

	if (ac != 2)
		return (write(1, "Too few args\n", 13), 1);
	if (av[1] == NULL)
		return (1);
	map = av[1];
	if (check_file(map) == 0)
		return (1);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}

}
