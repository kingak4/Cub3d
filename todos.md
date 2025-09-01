## Module 1: Scene Parsing & Validation

- [ ] **File Handling**: Create a function to read the `.cub` file line by line.
    
- [ ] **Element Parsing**:
    
    - [ ] Parse and store the paths for the four wall textures (
        
        `NO`, `SO`, `WE`, `EA`).
        
    - [ ] Parse and store the RGB values for the floor (
        
        `F`) and ceiling (`C`).
        
    - [ ] Ensure parsing is flexible, allowing for extra spaces and empty lines between elements.
    
- [ ]  **Map Parsing**: Read the map grid, which is always the last element in the file, into a 2D array (`char **`).
    
- [ ] **Data Validation**:
    
    - [ ] Check that all texture paths and color definitions are present and correctly formatted.
        
    - [ ] Validate the map characters, ensuring only
        
        `0`, `1`, , `N`, `S`, `E`, or `W` are used.
        
    - [ ] Confirm there is exactly one player start position (`N`, `S`, `E`, or `W`).
        
    - [ ] Validate that the map is completely enclosed by walls (
        
        `1`).
        

---

## Module 2: Initialization

- [ ] **Graphics (MLX) Setup**:
    
    - [ ] Initialize the MLX library.
        
    - [ ] Create a game window.
        
    - [ ] Create an image buffer that will act as your canvas for rendering frames.
        
- [ ] **Player Setup**:
    
    - [ ] Find the player's starting character (
        
        `N`, `S`, `E`, `W`) in the map to set their initial `(x, y)` coordinates.
        
    - [ ] Initialize the player's
        
        **direction vector** (`dirX`, `dirY`) based on their starting orientation.
        
    - [ ] Initialize the
        
        **camera plane vector** (`planeX`, `planeY`), which is perpendicular to the direction vector.
        

---

## Module 3: The Raycasting Engine

- [ ] **Main Loop Setup**: Create a loop that iterates through every vertical pixel column of the screen.
    
- [ ] **Ray & DDA Setup (Inside the loop)**:
    
    - [ ] Calculate the ray's initial direction for the current column
        
        `x`.
        
    - [ ] Determine the ray's starting map grid square (
        
        `mapX`, `mapY`).
        
    - [ ] Calculate
        
        `deltaDistX` and `deltaDistY`.
        
    - [ ] Calculate the initial
        
        `sideDistX` and `sideDistY`.
        
    - [ ] Determine the step direction (
        
        `stepX`, `stepY`).
        
- [ ] **DDA Algorithm**: Run the DDA loop that extends the ray one grid square at a time until it hits a wall.
    
- [ ] **Calculations Post-DDA**:
    
    - [ ] Calculate the
        
        **perpendicular distance** to the wall to avoid a "fish-eye" effect.
        
    - [ ] Determine
        
        `wall_x`, the exact horizontal coordinate on the wall where the ray hit.
        

---

## Module 4: Rendering to Screen

- [ ] **Preparation**:
    
    - [ ] Load the `.xpm` texture files into MLX image objects.
        
    - [ ] Create a helper function to place a single pixel of a given color into your main image buffer.
        
- [ ] **Drawing a Vertical Slice (for each column `x`)**:
    
    - [ ] Calculate the wall slice height on screen.
        
    - [ ] Determine the `draw_start` and `draw_end` y-coordinates for the wall slice.
        
    - [ ] **Draw Ceiling**: Draw a solid-colored vertical line from `y = 0` to `draw_start`.
        
    - [ ] **Draw Wall**: Draw a textured vertical line from `y = draw_start` to `draw_end`.
        
    - [ ] **Draw Floor**: Draw a solid-colored vertical line from `y = draw_end` to the bottom of the screen.
        
- [ ] **Frame Display**: After the loop for all `x` columns is finished, push the completed image buffer to the window.
    

---

## Module 5: Player Controls & Interaction

- [ ] **Event Handling**:
    
    - [ ] Hook into keyboard press events.
        
    - [ ] Hook into the window close event to allow graceful exit.
        
- [ ] **Player Rotation**: On left/right key press, apply the 2D rotation matrix to both the **direction vector** and the **camera plane vector**.
    
- [ ] **Player Movement**:
    
    - [ ] On W/S key press, calculate the new potential position by adding/subtracting the direction vector.
        
    - [ ] On A/D key press, calculate the new potential position by adding/subtracting the camera plane vector (for strafing).
        
    - [ ] **Implement Collision Detection**: Before updating the player's coordinates, check if the new position is inside a wall.
