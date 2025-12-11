/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:12:45 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/11 10:18:30 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* INCLUDES */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/src/libft.h"

/* MACROS */

# define SCREEN_W 1800
# define SCREEN_H 900
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* STRUCTS */

typedef struct s_player
{
	int				x;
	int				y;
	double			x_uni;
	double			y_uni;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}	t_player;

typedef struct s_ray
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			wallx;
	int				texx;
}	t_ray;

typedef struct s_plane
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_east;
	int				f_red;
	int				f_green;
	int				f_blue;
	int				c_red;
	int				c_green;
	int				c_blue;
	uint32_t		ccolor;
	uint32_t		fcolor;
}	t_plane;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			**map;
	int				map_width;
	int				map_height;
	t_plane			*plane;
	t_ray			*ray;
	t_player		*player;
}	t_data;

/* FUNCTION PROTOTYPES */

/* ============================================================ */
/*                        RAYCAST FUNCTIONS                     */
/* ============================================================ */

/**
 * @brief Initializes a ray for raycasting calculation for a specific screen
 * column
 * @param ray Pointer to ray structure to initialize
 * @param player Pointer to player structure containing position and direction
 * @param x Current screen column (0 to SCREEN_W-1)
 *
 * Calculates: camerax = 2*x/SCREEN_W - 1 (normalizes x to range [-1,1])
 * Calculates ray direction using: dir + plane * camerax (creates FOV effect)
 * Calculates deltadist = |1/raydir| (distance ray travels to cross
 * one grid line)
 */
void			init_ray(t_ray *ray, t_player *player, int x);

/**
 * @brief Calculates step direction and initial side distances for DDA algorithm
 * @param ray Pointer to ray structure to update
 * @param player Pointer to player structure with current position
 *
 * Determines step direction (-1 or +1) based on ray direction sign.
 * Calculates initial sidedist: distance from current position to next grid line.
 * Formula: sidedist = (next_grid_pos - current_pos) * deltadist
 */
void			calculate_step_and_side_dist(t_ray *ray, t_player *player);

/**
 * @brief Performs Digital Differential Analyzer (DDA) algorithm to find wall
 *  collision
 * @param ray Pointer to ray structure containing step and distance information
 * @param map 2D char array representing the game map ('1' = wall, '0' = empty)
 *
 * Iteratively steps through grid cells by choosing shortest sidedist.
 * Updates mapx/mapy coordinates and sidedist values each iteration.
 * Sets 'side' to indicate if wall hit was vertical (0) or horizontal (1).
 * Stops when hitting a wall character ('1').
 */
void			perform_dda(t_ray *ray, char **map);

/**
 * @brief Calculates perpendicular wall distance and screen drawing boundaries
 * @param ray Pointer to ray structure to update with distance calculations
 * @param player Pointer to player structure with current position
 *
 * Calculates perpendicular distance: (wall_pos - player_pos + offset) / raydir
 * This avoids fisheye effect by using perpendicular distance instead of actual
 *  distance.
 * Calculates wall height: SCREEN_H / perpendicular_distance
 * Determines drawstart/drawend: vertical pixel range to draw the wall on screen.
 */
void			calculate_wall_distance(t_ray *ray, t_player *player);

/**
 * @brief Executes complete raycasting process for a single screen column
 * @param data Pointer to main data structure containing all game information
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 *
 * Orchestrates the full raycasting pipeline:
 * 1. Initialize ray parameters, 2. Calculate DDA setup, 3. Perform wall
 *  detection,
 * 4. Calculate distances and screen boundaries, 5. Draw the resulting wall line.
 */
void			cast_single_ray(t_data *data, int x);

/**
 * @brief Calculates the x-coordinate for texture mapping on a wall
 * @param ray Pointer to ray structure with wall intersection information
 * @param player Pointer to player structure with position information
 * @param texture Pointer to the texture to be applied
 *
 * Determines the exact point where the ray hits the wall (wallx).
 * Converts wallx to texture coordinate (texx) based on texture width.
 * Flips texture coordinate when needed for correct orientation.
 */
void			calculate_texture_x(t_ray *ray, t_player *player,
					mlx_texture_t *texture);

/* ============================================================ */
/*                   RAYCAST RENDER FUNCTIONS                   */
/* ============================================================ */

/**
 * @brief Draws a vertical line representing a wall column on screen
 * @param data Pointer to main data structure containing image buffer
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 * @param ray Pointer to ray structure with drawing boundaries and wall info
 *
 * Selects appropriate texture based on wall direction.
 * Calculates texture x-coordinate for proper mapping.
 * Iterates from drawstart to drawend, sampling texture colors.
 * Uses mlx_put_pixel() to draw individual pixels on the image buffer.
 */
void			draw_vertical_line(t_data *data, int x, t_ray *ray);

/**
 * @brief Clears the screen by drawing ceiling and floor colors
 * @param data Pointer to main data structure containing image and color info
 *
 * Fills upper half of screen (y < SCREEN_H/2) with ceiling color.
 * Fills lower half of screen (y >= SCREEN_H/2) with floor color.
 * Creates the background before drawing walls on top.
 */
void			clear_background(t_data *data);

/**
 * @brief Renders a complete frame by casting rays for all screen columns
 * @param data Pointer to main data structure containing all game information
 *
 * First clears background with ceiling/floor colors.
 * Then iterates through all screen columns (x = 0 to SCREEN_W-1).
 * Calls cast_single_ray() for each column to build the complete 3D view.
 * This function creates the entire visible scene from the player's perspective.
 */
void			render_frame(t_data *data);

/* ============================================================ */
/*                      TEXTURE FUNCTIONS                       */
/* ============================================================ */

/**
 * @brief Loads all texture files specified in the configuration
 * @param data Pointer to main data structure containing texture paths
 *
 * Loads PNG textures for all four wall directions (N, S, E, W).
 * Cleans texture paths by removing whitespace and newlines.
 * Exits with error message if any texture fails to load.
 * Prints confirmation message for each successfully loaded texture.
 */
void			load_textures(t_data *data);

/**
 * @brief Extracts color from texture at specified coordinates
 * @param texture Pointer to MLX texture structure
 * @param x X-coordinate in texture (0 to texture width-1)
 * @param y Y-coordinate in texture (0 to texture height-1)
 * @return uint32_t RGBA color value at the specified pixel
 *
 * Clamps coordinates to valid texture bounds to prevent overflow.
 * Converts pixel bytes to 32-bit RGBA color format.
 * Handles different bytes_per_pixel values (RGB, RGBA).
 */
uint32_t		get_texture_color(mlx_texture_t *texture, int x, int y);

/**
 * @brief Selects the appropriate wall texture based on ray direction
 * @param data Pointer to main data structure containing all textures
 * @param ray Pointer to ray structure with direction and side information
 * @return mlx_texture_t* Pointer to the selected texture
 *
 * Checks ray->side to determine if wall is vertical (0) or horizontal (1).
 * For vertical walls: returns East texture if raydirx > 0, else West.
 * For horizontal walls: returns South texture if raydiry > 0, else North.
 */
mlx_texture_t	*select_texture(t_data *data, t_ray *ray);

/* ============================================================ */
/*                      PLAYER FUNCTIONS                        */
/* ============================================================ */

/**
 * @brief Initializes player position by finding player character on map
 * @param data Pointer to main data structure containing map and player info
 *
 * Searches through the map for player starting position (N, S, E, W).
 * Sets player's grid coordinates (x, y) and floating-point position.
 * Calls set_player_direction() to initialize direction vectors.
 * Calculates map dimensions after finding player position.
 */
void			init_player(t_data *data);

/**
 * @brief Sets player direction vectors based on starting orientation
 * @param player Pointer to player structure to initialize
 * @param orientation Character indicating direction ('N', 'S', 'E', or 'W')
 *
 * Sets dir_x/dir_y: direction vector the player is facing.
 * Sets plane_x/plane_y: camera plane perpendicular to direction (for FOV).
 * North: dir=(0,-1), plane=(0.66,0) | South: dir=(0,1), plane=(-0.66,0)
 * East: dir=(1,0), plane=(0,0.66) | West: dir=(-1,0), plane=(0,-0.66)
 */
void			set_player_direction(t_player *player, char orientation);

/**
 * @brief Calculates and stores the dimensions of the game map
 * @param data Pointer to main data structure containing map information
 *
 * Counts number of rows in map array to determine map height.
 * Finds longest row to determine map width.
 * Stores results in data->map_height and data->map_width.
 */
void			calculate_map_dimensions(t_data *data);

/* ============================================================ */
/*                      MOVEMENT FUNCTIONS                      */
/* ============================================================ */

/**
 * @brief Moves player position with collision detection
 * @param data Pointer to main data structure containing player and map
 * @param move_x X-axis movement delta (can be positive or negative)
 * @param move_y Y-axis movement delta (can be positive or negative)
 *
 * Calculates new position: new_pos = current_pos + move_delta
 * Checks collision by testing if map[new_y][new_x] != '1' (not a wall)
 * Only updates position if the new position is not inside a wall.
 * Updates both floating-point (x_uni/y_uni) and integer (x/y) coordinates.
 */
void			move_player(t_data *data, double move_x, double move_y);

/**
 * @brief Rotates player direction and camera plane by specified angle
 * @param data Pointer to main data structure containing player information
 * @param rot Rotation angle in radians (positive = clockwise)
 *
 * Applies 2D rotation matrix transformation:
 * new_dir_x = old_dir_x * cos(rot) - old_dir_y * sin(rot)
 * new_dir_y = old_dir_x * sin(rot) + old_dir_y * cos(rot)
 * Also rotates the camera plane vector to maintain proper FOV orientation.
 * This creates smooth camera rotation for looking left/right.
 */
void			rotate_player(t_data *data, double rot);

/**
 * @brief Processes continuous keyboard input for player movement and
 *  camera rotation
 * @param data Pointer to main data structure containing MLX and player info
 *
 * Checks key states using mlx_is_key_down() for smooth movement:
 * W/S: Forward/backward movement along direction vector * MOVE_SPEED
 * A/D: Strafe left/right movement along plane vector * MOVE_SPEED
 * LEFT/RIGHT arrows: Camera rotation by ±ROT_SPEED radians
 * All movements include collision detection via move_player().
 */
void			handle_movement(t_data *data);

/**
 * @brief Handles individual keypress events for discrete actions
 * @param keydata MLX key data structure containing key and action information
 * @param param Void pointer to main data structure (cast to t_data*)
 *
 * Processes ESC key to close window and exit program.
 * Called by MLX for each key press/release event.
 * Used for actions that should trigger once per keypress.
 */
void			handle_keypress(mlx_key_data_t keydata, void *param);

/* ============================================================ */
/*                         MLX FUNCTIONS                        */
/* ============================================================ */

/**
 * @brief Main game loop executed every frame
 * @param param Void pointer to main data structure (cast to t_data*)
 *
 * Called automatically by MLX every frame.
 * Processes player input via handle_movement().
 * Renders the current frame via render_frame().
 * Creates continuous gameplay loop.
 */
void			game_loop(void *param);

/**
 * @brief Initializes the MLX42 graphics library and sets up the game window
 * @param data Pointer to the main data structure containing all game information
 *
 * Sets up the MLX window with defined screen dimensions.
 * Creates the image buffer for rendering.
 * Initializes player position and loads textures.
 * Sets up hook functions for input and rendering.
 * Starts the main game loop with event handling.
 */
void			init_mlx(t_data *data);

/**
 * @brief Cleans up and frees all allocated resources
 * @param data Pointer to main data structure containing resources to free
 *
 * Deletes MLX textures (north, south, east, west).
 * Frees texture path strings from plane structure.
 * Frees the map 2D array.
 * Frees all allocated structs (plane, ray, player).
 * Prevents memory leaks on program exit.
 */
void			cleanup_data(t_data *data);

/* ============================================================ */
/*                       PARSER FUNCTIONS                       */
/* ============================================================ */

/**
 * @brief Reads and parses the .cub configuration file
 * @param filecub Path to the .cub file to read
 * @param data Pointer to main data structure to populate
 * @return int 1 on success, error message printed on failure
 *
 * Opens the specified .cub file.
 * Reads and processes configuration lines (textures, colors).
 * Extracts map data and stores it in data->map.
 * Closes file descriptor when done.
 */
int				read_cub(const char *filecub, t_data *data);

/**
 * @brief Parses texture paths and color values from configuration line
 * @param line Current line from .cub file being processed
 * @param data Pointer to main data structure
 * @param rgb Unused parameter (kept for compatibility)
 *
 * Identifies and parses texture lines (NO, SO, WE, EA).
 * Identifies and parses color lines (F for floor, C for ceiling).
 * Calls parse_color() to convert RGB values to RGBA format.
 */
void			textures_n_colors(char *line, t_data *data, char **rgb);

/**
 * @brief Converts RGB color components to RGBA 32-bit format
 * @param plane Pointer to plane structure containing RGB color values
 *
 * Combines ceiling RGB values into ccolor (R<<24 | G<<16 | B<<8 | 255).
 * Combines floor RGB values into fcolor (R<<24 | G<<16 | B<<8 | 255).
 * Alpha channel set to 255 (fully opaque).
 */
void			parse_color(t_plane *plane);

/**
 * @brief Reads all map lines from the file descriptor
 * @param fd File descriptor of opened .cub file
 * @param data Pointer to main data structure
 * @return char* String containing all map lines concatenated
 *
 * Uses get_next_line() to read file line by line.
 * Identifies map lines (starting with space, tab, digit, or '1').
 * Processes non-map lines as textures/colors.
 * Concatenates all map lines into single string.
 */
char			*read_map_lines(int fd, t_data *data);

/**
 * @brief Frees a 2D array of strings (map or split result)
 * @param map Pointer to 2D char array to free
 *
 * Iterates through all rows and frees each string.
 * Frees the array of pointers itself.
 * Sets pointer to NULL to avoid dangling references.
 */
void			free_map(char **map);

/**
 * @brief Prints the map to stdout for debugging purposes
 * @param map 2D char array representing the game map
 *
 * Iterates through all rows of the map.
 * Prints each row with its index number.
 * Used for visual verification during development.
 */
void			print_map_debug(char **map);

/* ============================================================ */
/*                    PARSER AUX FUNCTIONS                      */
/* ============================================================ */

/**
 * @brief Checks if a map line has walls at both ends
 * @param line String representing a single map row
 * @return int 1 if line is properly closed with walls, 0 otherwise
 *
 * Verifies first non-space character is '1' (wall).
 * Verifies last non-space character is '1' (wall).
 * Ensures map perimeter is enclosed.
 */
int				closed_line(char *line);

/**
 * @brief Gets the first non-space character in a line
 * @param line String to search
 * @return char First non-space character found
 *
 * Skips leading spaces and tabs.
 * Returns first meaningful character.
 * Used for perimeter validation.
 */
char			get_first(char *line);

/**
 * @brief Gets the last non-space character in a line
 * @param line String to search
 * @return char Last non-space character found
 *
 * Searches from end of string backwards.
 * Skips trailing spaces, tabs, and newlines.
 * Used for perimeter validation.
 */
char			get_last(char *line);

/**
 * @brief Validates that map perimeter is completely enclosed by walls
 * @param map 2D char array representing the game map
 * @return int 1 if perimeter is valid, 0 if there are gaps
 *
 * Checks first row is all '1' characters.
 * Checks last row is all '1' characters.
 * Checks each middle row starts and ends with '1'.
 * Ensures no escape routes from the map.
 */
int				check_perimeter(char **map);

/* ============================================================ */
/*                 PARSER AUX2 FUNCTIONS (MAP)                  */
/* ============================================================ */

/**
 * @brief Checks if a character is a valid playable space
 * @param c Character to check
 * @return int 1 if character is '0' or player (N,S,E,W), 0 otherwise
 *
 * Valid playable spaces: '0' (empty), 'N', 'S', 'E', 'W' (player).
 * Used to identify areas where player can move.
 */
int				is_playable(char c);

/**
 * @brief Checks if a character represents a valid map zone
 * @param c Character to check
 * @return int 1 if valid zone character, 0 otherwise
 *
 * Valid zones: '0', '1', 'N', 'S', 'E', 'W', ' ' (space).
 * Used to identify all acceptable map characters.
 */
int				valid_zone(char c);

/**
 * @brief Validates surroundings of a playable position
 * @param map 2D char array representing the game map
 * @param i Row index of position to check
 * @param j Column index of position to check
 * @return int 1 if surroundings are valid, 0 if hole detected
 *
 * Checks all 8 adjacent positions (including diagonals).
 * Ensures playable spaces are not adjacent to void/spaces.
 * Prevents holes that would allow escaping the map.
 */
int				check_zone(char **map, int i, int j);

/**
 * @brief Scans entire map for holes or invalid configurations
 * @param map 2D char array representing the game map
 * @return int 1 if map is valid, 0 if holes found
 *
 * Iterates through every position in the map.
 * For each playable position, calls check_zone().
 * Ensures map is properly enclosed and playable.
 */
int				check_hole(char **map);

/**
 * @brief Validates map configuration (player, textures, colors)
 * @param map 2D char array representing the game map
 * @param player Pointer to player structure to populate
 * @param plane Pointer to plane structure with configuration
 * @return int 1 if valid, 0 if validation fails
 *
 * Checks for exactly one player starting position.
 * Validates perimeter is closed with walls.
 * Checks for holes in the map.
 * Verifies textures and colors are configured.
 */
int				check_instances(char **map, t_player *player, t_plane *plane);

/* ============================================================ */
/*                 PARSER AUX3 FUNCTIONS (CONFIG)               */
/* ============================================================ */

/**
 * @brief Validates that all texture paths are defined
 * @param plane Pointer to plane structure containing texture paths
 * @return int 1 if all textures defined, 0 if any are missing
 *
 * Checks no_texture (North) is not NULL.
 * Checks so_texture (South) is not NULL.
 * Checks we_texture (West) is not NULL.
 * Checks ea_texture (East) is not NULL.
 */
int				check_textures(t_plane *plane);

/**
 * @brief Validates that floor and ceiling colors are in valid range
 * @param plane Pointer to plane structure containing RGB values
 * @return int 1 if colors valid (0-255), 0 if out of range
 *
 * Checks all RGB components (f_red, f_green, f_blue) are 0-255.
 * Checks all RGB components (c_red, c_green, c_blue) are 0-255.
 * Ensures color values can be properly displayed.
 */
int				check_colors(t_plane *plane);

/**
 * @brief Validates complete configuration (textures and colors)
 * @param plane Pointer to plane structure with all configuration
 * @return int 1 if configuration is complete and valid, 0 otherwise
 *
 * Calls check_textures() to verify all textures are defined.
 * Calls check_colors() to verify all color values are valid.
 * Returns 1 only if both checks pass.
 */
int				check_config(t_plane *plane);

/* ============================================================ */
/*                  PARSER PLAYER FUNCTIONS                     */
/* ============================================================ */

/**
 * @brief Checks if a character represents a player starting position
 * @param c Character to check
 * @return int 1 if character is N, S, E, or W, 0 otherwise
 *
 * Player starting positions indicated by direction character.
 * Used to identify and count player positions during parsing.
 */
int				is_player(char c);

/**
 * @brief Saves player position coordinates
 * @param player Pointer to player structure to update
 * @param x X-coordinate (column) on the map
 * @param y Y-coordinate (row) on the map
 *
 * Sets player->x to x coordinate.
 * Sets player->y to y coordinate.
 * Stores grid position for player starting location.
 */
void			save_player(t_player *player, int x, int y);

/**
 * @brief Searches map for player and validates single instance
 * @param map 2D char array representing the game map
 * @param player Pointer to player structure to populate
 * @param i Starting row index for search
 * @param j Starting column index for search
 * @return int 1 if exactly one player found, 0 otherwise
 *
 * Scans map from position (i,j) onwards.
 * Counts player characters (N, S, E, W).
 * Saves position and orientation if player found.
 * Returns error if zero or multiple players detected.
 */
int				check_player(char **map, t_player *player, int i, int j);

#endif