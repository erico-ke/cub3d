# cub3d

## RAYCASTING (Explicación de chatgpt basandose en https://lodev.org/cgtutor/raycasting.html)

Sure! Let’s **further break down the math** behind raycasting — particularly the **vector math**, **ray direction calculation**, and **DDA algorithm** — while keeping it as understandable and precise as possible.

---

### 🧮 1. Vectors: The Foundation of Raycasting

Raycasting in 2D uses **vectors** to represent:

* The **player's position**:

  $$
  \text{pos} = (x, y)
  $$

* The **direction the player is looking**:

  $$
  \text{dir} = (x, y)
  $$

  * This is a **unit vector** (usually) pointing forward.

* The **camera plane**:

  $$
  \text{plane} = (x, y)
  $$

  * This is **perpendicular** to `dir`.
  * Determines how wide the field of view (FOV) is.

> Think of `dir` as "forward", and `plane` as "left to right" across the screen.

---

### 🎯 2. Ray Direction for Each Screen Column

For every vertical stripe (`x`) of the screen:

* Map the column number to a value between -1 and 1:

  $$
  \text{cameraX} = 2x / \text{screenWidth} - 1
  $$

  * `x = 0` → `cameraX = -1` (left edge)
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

