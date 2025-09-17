/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:28:44 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/17 13:13:54 by erico-ke         ###   ########.fr       */
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
# include <MLX42/MLX42.h>
# include "libft.h"

/* MACROS */

# define SCREEN_W 800
# define SCREEN_H 600

/* STRUCTS */

typedef struct s_player
{
	int				x;
	int				y;
	int				x_uni;
	int				y_uni;
}	t_player;

typedef struct s_plane
{
	int				camerax;
	int				cameray;
	int				raydirx;
	int				raydiry;
	int				deltadistx;
	int				deltadisty;
	int				sidedistx;
	int				sidedisty;
}	t_plane;

typedef struct s_data
{
	mlx_t			*mlx;
	char			**map;
	int				map_width;
	int				map_height;
	t_plane			*plane;
	t_player		*player;
}	t_data;

#endif