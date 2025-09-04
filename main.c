/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:50:22 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/04 10:25:38 by kikwasni         ###   ########.fr       */
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
//int main(int ac, char *av[])
//{
//    int fd;
//    char **map;
//    t_pars data;

//    if (ac != 2)
//    {
//        write(1, "Usage: ./test <map_file>\n", 25);
//        return (1);
//    }

//    if (!check_file(av[1]))
//    {
//        write(1, "Wrong file extension\n", 21);
//        return (1);
//    }

//    fd = open(av[1], O_RDONLY);
//    if (fd < 0)
//    {
//        perror("Error opening file");
//        return (1);
//    }

//    // inicjalizacja struktury
//    data.n_wall = NULL;
//    data.s_wall = NULL;
//    data.e_wall = NULL;
//    data.w_wall = NULL;
//    data.floor = 0;
//    data.celling = 0;

//    // wczytanie pliku
//    map = read_file(fd, &data);
//    close(fd);

//    // test - wypisanie nagłówków
//    printf("North wall: %s\n", data.n_wall);
//    printf("South wall: %s\n", data.s_wall);
//    printf("East wall: %s\n", data.e_wall);
//    printf("West wall: %s\n", data.w_wall);
//    printf("Floor: 0x%06X\n", data.floor);
//    printf("Celling: 0x%06X\n", data.celling);

//    // test - wypisanie mapy
//    int i = 0;
//    while (map && map[i])
//    {
//        printf("%s\n", map[i]);
//        free(map[i]);
//        i++;
//    }
//    free(map);

//    return (0);
//}

//int main(int argc, char **argv)
//{
//	t_pars data;
//	int fd;

//	if (argc != 2)
//		return (write(1, "Usage: ./cub3d <map.cub>\n", 26), 1);

//	init_pars(&data);   // <<< tutaj inicjalizacja
//	fd = open(argv[1], O_RDONLY);
//	if (fd < 0)
//		return (write(1, "Error: cannot open file\n", 24), 1);

//	read_file(fd, &data);

//	// sprawdzenie czy działa
//	printf("North wall: %s\n", data.n_wall);
//	printf("South wall: %s\n", data.s_wall);
//	printf("East wall: %s\n", data.e_wall);
//	printf("West wall: %s\n", data.w_wall);
//	printf("Floor: %#08x\n", data.floor);
//	printf("Celling: %#08x\n", data.celling);

//	free(data.n_wall);
//	free(data.s_wall);
//	free(data.e_wall);
//	free(data.w_wall);
//	close(fd);
//	return (0);
//}
int main(int argc, char **argv)
{
    t_pars data;
	t_vector2 node;
    int fd;
    int i;

    if (argc != 2)
        return (write(1, "Usage: ./cub3d <map.cub>\n", 26), 1);

    init_pars(&data, &node);   // inicjalizacja struktury

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (write(1, "Error: cannot open file\n", 24), 1);

    read_file(fd, &data);  // mapa wczytywana do data.map
    close(fd);

     //sprawdzenie danych w t_pars
    printf("North wall: %s\n", data.n_wall);
    printf("South wall: %s\n", data.s_wall);
    printf("East wall: %s\n", data.e_wall);
    printf("West wall: %s\n", data.w_wall);
    printf("Floor: %#08x\n", data.floor);
    printf("Celling: %#08x\n", data.celling);

    // sprawdzenie mapy
    if (!data.map)
        printf("Mapa nie została poprawnie wczytana.\n");
    else
    {
        printf("Mapa wczytana poprawnie:\n");
        i = 0;
        while (data.map[i])
        {
            printf("%s\n", data.map[i]);
            i++;
        }
    }
	if (find_palyer(&node, &data))
	{
		printf("player x =  %d\n", node.x);
		printf("player y =  %d\n", node.y);
	}
	else
		printf("brak gracza\n");

    free(data.n_wall);
    free(data.s_wall);
    free(data.e_wall);
    free(data.w_wall);

    if (data.map)
    {
        i = 0;
        while (data.map[i])
            free(data.map[i++]);
        free(data.map);
    }
    return 0;
}
