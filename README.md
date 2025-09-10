# Hello, this is my take on 42 Warsaw project called "cub3D".

This project is about building a realistic 3D graphical representation of the inside of a maze from a first-person perspective using ray-casting principles. As a student I need to follow rules such as: limited usage of external libraries, all the code needs to follow the 42 norm.

The game is inspired by the world-famous Wolfenstein 3D game, which is considered the first FPS ever created, and is built on top of 42's MiniLibX graphics library.

**1. To run the game clone this repo first:**
```bash
git clone [your-repository-url]
cd Cub3d
```

**2. Now we need to get minilibx library, in bash use command:**
```bash
bash import_libX.sh
```
> [!NOTE]
> This bash command will clone and build this repository.

**3. Build the game with command:**
```bash
make
```

**4. Launch the game, to do that you need to use:**
```bash
./cub3D maps/map.cub
```
> [!NOTE]
> Maps are in folder ./maps, also you can create your own unique map.

## Controls
- **W, A, S, D** - Move through the maze
- **Left/Right Arrow Keys** - Look left and right in the maze
- **ESC** - Exit the game
- **Red Cross (X)** - Close window and quit

## Features
- **Ray-casting 3D rendering** - Experience realistic 3D graphics
- **Different wall textures** - Walls display different textures based on direction (North, South, East, West)
- **Customizable colors** - Set floor and ceiling to different colors
- **Smooth window management** - Responsive window handling

## Create your own map

The game reads maps in .cub format that follow specific rules provided in the project subject.

### Map rules:
1. Map file must be in .cub format
2. Map must be closed/surrounded by walls
3. Map must be composed of only these characters: **0, 1, N, S, E, W**
   - `'0'` - Empty space
   - `'1'` - Wall
   - `'N'` - Player start position facing North
   - `'S'` - Player start position facing South
   - `'E'` - Player start position facing East
   - `'W'` - Player start position facing West

### Required elements in .cub file:
```
NO ./path_to_north_texture    # North wall texture
SO ./path_to_south_texture    # South wall texture
WE ./path_to_west_texture     # West wall texture
EA ./path_to_east_texture     # East wall texture

F 220,100,0                   # Floor color (R,G,B)
C 225,30,0                    # Ceiling color (R,G,B)

111111
100101
101001
1100N1
111111
```

**Example of a valid .cub file:**
```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**To create your map:**
1. Enter the `./maps` directory
2. Create a new file with `.cub` extension
3. Follow the format shown above
4. Include all required textures and colors
5. Design your maze layout

**Launch your custom map:**
```bash
./cub3D ./maps/[map_name].cub
```

> [!WARNING]
> If any misconfiguration is encountered in the file, the program will exit and return "Error\n" followed by an explicit error message.

## Technical Details
- **Language:** C
- **Graphics Library:** MiniLibX
- **Compilation Flags:** -Wall -Wextra -Werror
- **External Functions:** open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday, math library functions, MiniLibX functions

---

*This project explores ray-casting mathematics and provides a playful practical application of mathematical concepts to create elegant and efficient algorithms for 3D rendering.*
