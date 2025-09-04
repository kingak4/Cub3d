/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kikwasni <kikwasni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 11:50:22 by kikwasni          #+#    #+#             */
/*   Updated: 2025/09/04 10:41:09 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_pars data;
    int fd;
    int i;

    if (argc != 2)
        return (write(1, "Usage: ./cub3d <map.cub>\n", 26), 1);

    init_pars(&data);   // inicjalizacja struktury

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (write(1, "Error: cannot open file\n", 24), 1);

    read_file(fd, &data);  // mapa wczytywana do data.map
    close(fd);

    // sprawdzenie danych w t_pars
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

	//wywołanie głównej funkcji od raycastów
	main_raycaster(&data);

    // zwalnianie pamięci
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
