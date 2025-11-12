/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:12:45 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 16:24:10 by fracurul         ###   ########.fr       */
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

# define SCREEN_W 1200
# define SCREEN_H 600
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
}	t_ray;

typedef struct s_plane
{
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

/**
 * @brief Initializes the MLX42 graphics library and sets up the game window
 * @param data Pointer to the main data structure containing game info
 *
 * Sets up the MLX window, creates the image buffer, calculates map dimensions,
 * and starts the main game loop with event handling.
 */
void		init_mlx(t_data *data);

/**
 * @brief Calculates the dimensions (width and height) of the loaded map
 * @param data Pointer to the main data structure containing map information
 *
 * Counts the number of rows in the map for height.
 * Finds the longest row length for width to handle irregular map shapes.
 * Updates data->map_width and data->map_height fields.
 */
void		calculate_map_dimensions(t_data *data);

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
void		init_ray(t_ray *ray, t_player *player, int x);

/**
 * @brief Calculates step direction and initial side distances for DDA algorithm
 * @param ray Pointer to ray structure to update
 * @param player Pointer to player structure with current position
 *
 * Determines step direction (-1 or +1) based on ray direction sign.
 * Calculates initial sidedist: distance from current pos to next grid line.
 * Formula: sidedist = (next_grid_pos - current_pos) * deltadist
 */
void		calculate_step_and_side_dist(t_ray *ray, t_player *player);

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
void		perform_dda(t_ray *ray, char **map);

/**
 * @brief Calculates perpendicular wall distance and screen drawing boundaries
 * @param ray Pointer to ray structure to update with distance calculations
 * @param player Pointer to player structure with current position
 *
 * Calculates perpendicular distance: (wall_pos - player_pos + offset) / raydir
 * This avoids fisheye effect by using perpendicular distance instead of actual
 *  distance.
 * Calculates wall height: SCREEN_H / perpendicular_distance
 * Determines drawstart/drawend: vertical pixel range to draw wall on screen.
 */
void		calculate_wall_distance(t_ray *ray, t_player *player);

/**
 * @brief Draws a vertical line representing a wall column on screen
 * @param data Pointer to main data structure containing image buffer
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 * @param ray Pointer to ray structure with drawing boundaries and wall info
 *
 * Gets wall color based on direction and applies shading for horizontal walls.
 * Iterates from drawstart to drawend, setting each pixel to the wall color.
 * Uses mlx_put_pixel() to draw individual pixels on the image buffer.
 */
void		draw_vertical_line(t_data *data, int x, t_ray *ray);

/**
 * @brief Executes complete raycasting process for a single screen column
 * @param data Pointer to main data structure containing all game information
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 *
 * Orchestrates the full raycasting pipeline:
 * 1. Initialize ray parameters, 2. Calculate DDA setup, 3. Perform wall
 *  detection,
 * 4. Calculate distances and screen boundaries, 5. Draw resulting wall line.
 */
void		cast_single_ray(t_data *data, int x);

/**
 * @brief Clears the screen by drawing ceiling and floor colors
 * @param data Pointer to main data structure containing image and color info
 *
 * Fills upper half of screen (y < SCREEN_H/2) with ceiling color.
 * Fills lower half of screen (y >= SCREEN_H/2) with floor color.
 * Creates the background before drawing walls on top.
 */
void		clear_background(t_data *data);

/**
 * @brief Renders a complete frame by casting rays for all screen columns
 * @param data Pointer to main data structure containing all game information
 *
 * First clears background with ceiling/floor colors.
 * Then iterates through all screen columns (x = 0 to SCREEN_W-1).
 * Calls cast_single_ray() for each column to build the complete 3D view.
 * This function creates the entire visible scene from the player's perspective.
 */
void		render_frame(t_data *data);

/**
 * @brief Determines wall color based on ray direction and applies shading
 * @param ray Pointer to ray structure containing direction and side information
 * @return uint32_t RGBA color value for the wall
 *
 * Assigns different colors based on wall orientation:
 * - North/South walls (side==1): Red (south) or Green (north)
 * - East/West walls (side==0): Blue (east) or Yellow (west)
 * Applies shading: horizontal walls are darker (color >> 1) for depth effect.
 */
uint32_t	get_wall_color(t_ray *ray);

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
void		move_player(t_data *data, double move_x, double move_y);

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
void		rotate_player(t_data *data, double rot);

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
void		handle_movement(t_data *data);

/* PARSER FUNCTIONS */
int			read_map(const char *filecub, t_data *data);
void		free_map(char **map);

/**
 * @brief Checks if a line contains only valid map characters
 * @param line String to check
 * @return int 1 if valid map line, 0 otherwise
 *
 * Valid map characters: '0' (empty), '1' (wall), ' ' (space),
 * 'N' 'S' 'E' 'W' (player positions)
 */
int			is_map_line(char *line);

/**
 * @brief Extracts only the map portion from all file lines
 * @param all_lines Array of all lines from the .cub file
 * @return char** Array containing only map lines, NULL on error
 *
 * Separates map content from configuration (textures, colors).
 * Map must be the last section in the file according to subject.
 */
char		**extract_map_lines(char **all_lines);

/**
 * @brief Finds the player position and orientation in the map
 * @param map 2D char array representing the game map
 * @param player Pointer to player structure to initialize
 * @return int 0 on success, 1 on error (no player found or multiple players)
 *
 * Searches for exactly one player character (N, S, E, W) in the map.
 * Sets player position (x, y) and direction vectors based on orientation:
 * - N (North): dir_y = -1, dir_x = 0, plane_x = 0.66
 * - S (South): dir_y = 1, dir_x = 0, plane_x = -0.66
 * - E (East): dir_x = 1, dir_y = 0, plane_y = 0.66
 * - W (West): dir_x = -1, dir_y = 0, plane_y = -0.66
 * Replaces player character with '0' (empty space) after finding it.
 */
int			find_player_position(char **map, t_player *player);

/**
 * @brief Sets player direction and camera plane based on orientation character
 * @param player Pointer to player structure to update
 * @param orientation Character indicating direction (N, S, E, W)
 *
 * Configures direction vector (where player looks) and camera plane vector
 * (perpendicular to direction, determines FOV width):
 * Camera plane length of 0.66 provides ~60 degree field of view.
 */
void		set_player_orientation(t_player *player, char orientation);

/**
 * @brief Validates that the map contains exactly one player
 * @param map 2D char array representing the game map
 * @return int Number of players found (should be exactly 1)
 *
 * Counts occurrences of player characters (N, S, E, W) in the map.
 * Returns count for validation - exactly 1 player required for valid map.
 */
int			count_players_in_map(char **map);

/**
 * @brief Search for player character in the map and set its position
 * @param map 2D char array representing the game map
 * @param player Pointer to player structure to update
 * @return int 0 on success, 1 on error
 *
 * Internal function to locate and set player position after validation.
 */
int			search_player_in_map(char **map, t_player *player);

#endif