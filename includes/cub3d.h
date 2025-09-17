/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:28:44 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/17 11:52:15 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
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

# define SCREEN_W 800
# define SCREEN_H 600

typedef struct s_data
{
	mlx_t			*mlx;
	char			**map;
	int				map_width;
	int				map_height;
	double			player_x;
	double			player_y;
	double			player_angle;
}t_data;



#endif