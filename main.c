
#include "cub3d.h"

int main(int argc, char **argv)
{
	t_pars data;
	t_vector2 node;
	int fd;
	int i;

	if (argc != 2)
		return (write(1, "Usage: ./cub3d <map.cub>\n", 26), 1);

	init_pars(&data, &node); // inicjalizacja struktury

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(1, "Error: cannot open file\n", 24), 1);

	read_file(fd, &data); // mapa wczytywana do data.map
	close(fd);

	if (check_textures(&data) && is_player(&node, &data) && is_map_ok(&data))
	{
		// sprawdzenie danych w t_pars
		printf("North wall: %s\n", data.n_wall);
		printf("South wall: %s\n", data.s_wall);
		printf("East wall: %s\n", data.e_wall);
		printf("West wall: %s\n", data.w_wall);
		printf("Floor: %#08x\n", data.floor);
		printf("Celling: %#08x\n", data.celling);

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
		get_map_size(&data);
		printf("w =  %d\n", data.w);
			printf("h = %d\n", data.h);
		printf("player dir: %c\n", data.player_dir_char);
		
	}
	// sprawdzenie mapy

	data.node = &node;
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
