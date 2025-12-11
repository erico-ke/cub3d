/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:12:45 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/11 10:11:32 by erico-ke         ###   ########.fr       */
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

/**
 * @brief Initializes the MLX42 graphics library and sets up the game window
 * @param data Pointer to the main data structure containing all game information
 *
 * Sets up the MLX window, creates the image buffer, initializes player position,
 * creates test map, and starts the main game loop with event handling.
 */
void			init_mlx(t_data *data);

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
 * @brief Draws a vertical line representing a wall column on screen
 * @param data Pointer to main data structure containing image buffer
 * @param x Screen column coordinate (0 to SCREEN_W-1)
 * @param ray Pointer to ray structure with drawing boundaries and wall info
 *
 * Gets wall color based on direction and applies shading for horizontal walls.
 * Iterates from drawstart to drawend, setting each pixel to the wall color.
 * Uses mlx_put_pixel() to draw individual pixels on the image buffer.
 */
void			draw_vertical_line(t_data *data, int x, t_ray *ray);

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
uint32_t		get_wall_color(t_ray *ray);

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

/* CLEANUP FUNCTIONS */
void			cleanup_data(t_data *data);

/* PLAYER FUNCTIONS */
void			init_player(t_data *data);
void			set_player_direction(t_player *player, char orientation);
void			calculate_map_dimensions(t_data *data);

/* MLX FUNCTIONS */
void			handle_keypress(mlx_key_data_t keydata, void *param);
void			game_loop(void *param);
void			init_mlx(t_data *data);

/* RAYCAST FUNCTIONS */
void			cast_single_ray(t_data *data, int x);
void			render_frame(t_data *data);
void			calculate_texture_x(t_ray *ray, t_player *player,
					mlx_texture_t *texture);
void			draw_vertical_line(t_data *data, int x, t_ray *ray);

/* TEXTURE FUNCTIONS */
void			load_textures(t_data *data);
uint32_t		get_texture_color(mlx_texture_t *texture, int x, int y);
mlx_texture_t	*select_texture(t_data *data, t_ray *ray);

/* PARSER FUNCTIONS */
int				read_cub(const char *filecub, t_data *data);
void			textures_n_colors(char *line, t_data *data, char **rgb);
void			parse_color(t_plane *plane);
char			*read_map_lines(int fd, t_data *data);
void			free_map(char **map);
void			print_map_debug(char **map);

/* PASER AUX FUNCS*/
int				closed_line(char *line);
char			get_first(char *line);
char			get_last(char *line);
int				check_perimeter(char **map);
int				is_player(char c);
void			save_player(t_player *player, int x, int y);
int				check_player(char **map, t_player *player, int i, int j);
int				is_playable(char c);
int				valid_zone(char c);
int				check_zone(char **map, int i, int j);
int				check_hole(char **map);
int				check_instances(char **map, t_player *player, t_plane *plane);
int				check_textures(t_plane *plane);
int				check_colors(t_plane *plane);
int				check_config(t_plane *plane);

#endif