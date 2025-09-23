/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:28:44 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/23 16:29:18 by erico-ke         ###   ########.fr       */
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

void	init_mlx(t_data *data);
void	init_ray(t_ray *ray, t_player *player, int x);
void	calculate_step_and_side_dist(t_ray *ray, t_player *player);
void	perform_dda(t_ray *ray, char **map);
void	calculate_wall_distance(t_ray *ray, t_player *player);
void	draw_vertical_line(t_data *data, int x, t_ray *ray);
void	cast_single_ray(t_data *data, int x);
void	clear_background(t_data *data);
void	render_frame(t_data *data);
uint32_t	get_wall_color(t_ray *ray);
void	move_player(t_data *data, double move_x, double move_y);
void	rotate_player(t_data *data, double rot);
void	handle_movement(t_data *data);

#endif