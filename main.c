/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:50:22 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/01 18:13:18 by kikwasni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//int main(int ac, char *av[])
//{
//	char	*map;
//	int		fd;

//	if (ac != 2)
//		return (write(1, "Too few args\n", 13), 1);
//	if (av[1] == NULL)
//		return (1);
//	map = av[1];
//	if (check_file(map) == 0)
//		return (1);
//	fd = open(map, O_RDONLY);
//	if (fd < 0)
//	{
//		perror("Error opening file");
//		return (1);
//	}
	
//}
int main(int ac, char *av[])
{
    int fd;
    char **map;
    t_pars data;

    if (ac != 2)
    {
        write(1, "Usage: ./test <map_file>\n", 25);
        return (1);
    }

    if (!check_file(av[1]))
    {
        write(1, "Wrong file extension\n", 21);
        return (1);
    }

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    // inicjalizacja struktury
    data.n_wall = NULL;
    data.s_wall = NULL;
    data.e_wall = NULL;
    data.w_wall = NULL;
    data.floor = 0;
    data.celling = 0;

    // wczytanie pliku
    map = read_file(fd, &data);
    close(fd);

    // test - wypisanie nagłówków
    printf("North wall: %s\n", data.n_wall);
    printf("South wall: %s\n", data.s_wall);
    printf("East wall: %s\n", data.e_wall);
    printf("West wall: %s\n", data.w_wall);
    printf("Floor: 0x%06X\n", data.floor);
    printf("Celling: 0x%06X\n", data.celling);

    // test - wypisanie mapy
    int i = 0;
    while (map && map[i])
    {
        printf("%s\n", map[i]);
        free(map[i]);
        i++;
    }
    free(map);

    return (0);
}

