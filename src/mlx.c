/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:07:23 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/23 16:07:20 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(SCREEN_W, SCREEN_H, "Cub3D", true);
	if (!data->mlx)
	{
		perror("Error initializing MLX");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(data->mlx, &handle_keypress, data);
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	if (!data->img)
	{
		perror("Error creating image");
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);

	int x;
	int y;
	x = 0;
	y = 0;
	data->plane = malloc(sizeof(t_plane));
	if (!data->plane)
	{
		perror("Error: plane not initialized");
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->plane->ccolor = 0x87CEEB;
	data->plane->fcolor = 0xAAAAAA;
	for (y = 0; y < SCREEN_H; y++)
	{
		for (x = 0; x < SCREEN_W; x++)
		{
			if (y < SCREEN_H / 2)
				mlx_put_pixel(data->img, x, y, data->plane->ccolor);
			else
				mlx_put_pixel(data->img, x, y, data->plane->fcolor);
		}
	}
	mlx_loop(data->mlx);
}
