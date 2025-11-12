# cub3D

## My first RayCaster with miniLibX

### 📋 Project Overview

**cub3D** is a 3D graphical representation project inspired by the world-famous **Wolfenstein 3D** game, considered the first FPS ever created. The project implements ray-casting principles to create a realistic first-person perspective view inside a maze.

### 🎯 Objectives

This project focuses on:
- **Rigor and C programming**: Following 42 coding standards and best practices
- **Basic algorithms**: Implementing mathematical algorithms for 3D rendering
- **Graphics programming**: Working with windows, colors, events, and pixel manipulation
- **Mathematical applications**: Using mathematics as a tool for elegant and efficient algorithms

### 🛠 Technical Specifications

#### Requirements
- **Language**: C
- **Graphics Library**: MLX42 (MiniLibX)
- **Compilation**: `cc` with flags `-Wall -Wextra -Werror`
- **External Functions**: 
  - Standard: `open, close, read, write, printf, malloc, free, perror, strerror, exit`
  - Math library: All functions (`-lm`)
  - System: `gettimeofday()`
  - Graphics: All MLX42 functions

#### Controls
- **W, A, S, D**: Move through the maze (forward, left, backward, right)
- **Left/Right Arrow Keys**: Look left and right in the maze
- **ESC**: Exit the program
- **Red Cross**: Close window and exit

### 📁 File Format (.cub)

The program takes a scene description file with `.cub` extension containing:

#### Map Elements
- **`0`**: Empty space
- **`1`**: Wall
- **`N`, `S`, `E`, `W`**: Player starting position and orientation

#### Configuration Elements
```
NO ./path_to_the_north_texture    # North wall texture
SO ./path_to_the_south_texture    # South wall texture  
WE ./path_to_the_west_texture     # West wall texture
EA ./path_to_the_east_texture     # East wall texture
F 220,100,0                       # Floor color (R,G,B)
C 225,30,0                        # Ceiling color (R,G,B)
```

#### Example Map
```
111111
100101
101001
1100N1
111111
```

### 🏗 Architecture

#### Core Structures
- **`t_player`**: Player position, direction, and camera plane
- **`t_ray`**: Ray casting calculations and wall detection
- **`t_data`**: Main game state including MLX, map, and rendering data

#### Key Functions

**Parser Functions**:
- `find_player_position()`: Locates player (N,S,E,W) and sets initial orientation
- `extract_map_lines()`: Separates map from configuration data
- `count_players_in_map()`: Validates exactly one player exists

**Rendering Pipeline**:
1. `init_ray()`: Initialize ray parameters for screen column
2. `calculate_step_and_side_dist()`: Setup DDA algorithm
3. `perform_dda()`: Find wall collision using Digital Differential Analyzer  
4. `calculate_wall_distance()`: Compute perpendicular distance (prevents fisheye)
5. `draw_vertical_line()`: Render wall column with proper height

**Player System**:

- `move_player()`: Movement with collision detection
- `rotate_player()`: Camera rotation using 2D rotation matrices  
- `set_player_orientation()`: Configure initial direction based on map character

### 🧮 Ray Casting Algorithm

The ray casting implementation follows these mathematical principles:

#### Vector Mathematics
- **Player Position**: `(x, y)` coordinates in the 2D map
- **Direction Vector**: `(dir_x, dir_y)` - where the player is looking
- **Camera Plane**: `(plane_x, plane_y)` - perpendicular to direction, determines FOV

#### Ray Direction Calculation
For each screen column `x`:

```
cameraX = 2 * x / screenWidth - 1
rayDir = direction + plane * cameraX
```

#### DDA (Digital Differential Analyzer)
The algorithm steps through grid cells to find wall intersections:

1. **Calculate delta distances**: How far the ray travels to cross one grid line
2. **Determine step direction**: +1 or -1 based on ray direction
3. **Step through grid**: Choose shortest distance at each iteration
4. **Detect collision**: Stop when hitting a wall ('1' character)

#### Distance Calculation
Uses **perpendicular wall distance** to avoid fisheye effect:

```
perpWallDist = (wallPos - playerPos + offset) / rayDir
wallHeight = screenHeight / perpWallDist
```

### 🎮 Features Implemented

#### ✅ Mandatory Features
- ✅ 3D graphical representation using ray-casting
- ✅ Different wall textures for each direction (N, S, E, W)
- ✅ Floor and ceiling color configuration
- ✅ Smooth player movement (WASD keys)
- ✅ Camera rotation (arrow keys)
- ✅ Proper window management
- ✅ Map validation (closed by walls)
- ✅ Player position detection and orientation setup
- ✅ Error handling with descriptive messages

#### 🚧 Potential Bonus Features
- Wall collision detection
- Minimap system
- Doors that can open/close
- Animated sprites  
- Mouse rotation

### 🚀 Compilation and Usage

#### Build
```bash
make
```

#### Clean
```bash
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild from scratch
```

#### Run
```bash
./cub3d path/to/map.cub
```

### 📝 Map Validation Rules

The program validates that:

1. **File format**: Must have `.cub` extension
2. **Player count**: Exactly one player character (N, S, E, W)
3. **Map closure**: Map must be surrounded by walls ('1')
4. **Valid characters**: Only '0', '1', ' ', 'N', 'S', 'E', 'W' in map
5. **Configuration**: All texture paths and colors must be specified
6. **Map position**: Map must be the last element in the file

### 🏗 Project Structure

```
cub3d/
├── Makefile              # Build configuration
├── includes/
│   └── cub3d.h          # Header with all declarations
├── libs/
│   ├── MLX42/           # Graphics library
│   └── libft/           # Custom C library
├── src/
│   ├── main.c           # Program entry point
│   ├── parser.c         # Map and config parsing
│   ├── mlx.c            # MLX initialization and controls
│   └── raycast.c        # Ray casting implementation
├── example.cub          # Sample map file
└── README.md            # This documentation
```

### 🎯 Learning Outcomes

This project develops skills in:

- **Computer graphics fundamentals**: Understanding 3D projection
- **Mathematical applications**: Vector math, trigonometry, linear algebra
- **Algorithm optimization**: Efficient ray-map intersection  
- **Memory management**: Proper allocation/deallocation in C
- **Event-driven programming**: Real-time input handling
- **Software architecture**: Modular design and clean code organization

### 📚 References

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Technical Details](http://users.atw.hu/wolf3d/)
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42)

---

*This project is part of the 42 School curriculum, focusing on graphics programming and mathematical algorithm implementation.*
  * `x = screenWidth/2` → `cameraX = 0` (center)
  * `x = screenWidth - 1` → `cameraX = 1` (right edge)

Then calculate the direction of the ray for this column:

$$
\text{rayDir} = \text{dir} + \text{plane} \times \text{cameraX}
$$

> So every ray is a slightly rotated version of the player’s forward direction, based on its position on the screen.

---

### 🔁 3. DDA (Digital Differential Analyzer) Algorithm

DDA helps find **where a ray first hits a wall** by stepping through the grid **cell-by-cell**. Here's how the math works:

#### Step 1: Find the current grid square the player is in:

$$
\text{mapX} = \text{int}(pos.x) \quad , \quad \text{mapY} = \text{int}(pos.y)
$$

#### Step 2: Calculate the ray direction components:

$$
\text{rayDirX}, \text{rayDirY}
$$

#### Step 3: Calculate how far we must travel to cross one x or y grid line:

$$
\text{deltaDistX} = \left| \frac{1}{\text{rayDirX}} \right| \quad , \quad \text{deltaDistY} = \left| \frac{1}{\text{rayDirY}} \right|
$$

* This tells how far the ray needs to move along the ray direction to move by 1 unit in x or y.

#### Step 4: Determine step direction and initial side distances:

```cpp
if (rayDirX < 0) {
    stepX = -1;
    sideDistX = (pos.x - mapX) * deltaDistX;
} else {
    stepX = 1;
    sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
}

if (rayDirY < 0) {
    stepY = -1;
    sideDistY = (pos.y - mapY) * deltaDistY;
} else {
    stepY = 1;
    sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
}
```

#### Step 5: Perform the DDA loop:

* At each step, move to the **next closest square** (either in x or y direction), based on which side distance is smaller:

```cpp
while (hit == false) {
    if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;  // hit vertical side
    } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;  // hit horizontal side
    }

    // Check if ray hit a wall at map[mapX][mapY]
    if (worldMap[mapX][mapY] > 0) hit = true;
}
```

---

### 📏 4. Calculate Wall Distance

After hitting the wall, compute **perpendicular wall distance** (to avoid fish-eye distortion):

```cpp
if (side == 0)
    perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDirX;
else
    perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDirY;
```

---

### 🧱 5. Projecting the Wall on Screen

Now convert the distance to a line height on screen:

$$
\text{lineHeight} = \frac{\text{screenHeight}}{\text{perpWallDist}}
$$

Then compute the start and end y-coordinates to draw the vertical stripe of the wall:

```cpp
int drawStart = -lineHeight / 2 + screenHeight / 2;
int drawEnd = lineHeight / 2 + screenHeight / 2;
```

---

### 📌 Summary Table of Key Variables

| Variable       | Meaning                               |
| -------------- | ------------------------------------- |
| `pos`          | Player position vector `(x, y)`       |
| `dir`          | View direction vector                 |
| `plane`        | Camera plane (perpendicular to `dir`) |
| `rayDir`       | Direction of current ray              |
| `deltaDistX/Y` | Distance to next x/y grid line        |
| `sideDistX/Y`  | Accumulated distance to next side     |
| `stepX/Y`      | Direction to step in map grid         |
| `perpWallDist` | Corrected wall distance               |
| `lineHeight`   | Height of wall to draw                |

