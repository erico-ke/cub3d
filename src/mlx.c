/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:03 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 16:43:35 by fracurul         ###   ########.fr       */
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
		free_map(data->map);
		free(data->player);
		free(data->plane);
		free(data);
		exit(EXIT_SUCCESS);
	}
}



//Count the number of rows in the map
static void	count_map_height(t_data *data)
{
	int	i;

	data->map_height = 0;
	i = 0;
	while (data->map[i])
	{
		data->map_height++;
		i++;
	}
}

//Find the width of the widest row in the map
static void	find_map_width(t_data *data)
{
	int	i;
	int	len;

	data->map_width = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > data->map_width)
			data->map_width = len;
		i++;
	}
}

void	calculate_map_dimensions(t_data *data)
{
	if (!data->map)
		return;
	count_map_height(data);
	find_map_width(data);
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_movement(data);
	render_frame(data);
}

//Initialize MLX window and basic setup
static void	init_mlx_window(t_data *data)
{
	ft_printf("Attempting to initialize MLX...\n");
	data->mlx = mlx_init(SCREEN_W, SCREEN_H, "Cub3D", true);
	if (!data->mlx)
	{
		ft_printf("MLX initialization failed!\n");
		perror("Error initializing MLX");
		exit(EXIT_FAILURE);
	}
	ft_printf("MLX initialized successfully!\n");
	mlx_key_hook(data->mlx, &handle_keypress, data);
}

//Create MLX image and set up rendering
static void	init_mlx_image(t_data *data)
{
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	if (!data->img)
	{
		perror("Error creating image");
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

//Initialize plane colors and settings
static void	init_plane_data(t_data *data)
{
	data->plane = malloc(sizeof(t_plane));
	if (!data->plane)
	{
		perror("Error: plane not initialized");
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->plane->ccolor = 0x87CEEBFF;
	data->plane->fcolor = 0x8B4513FF;
}

void	init_mlx(t_data *data)
{
	init_mlx_window(data);
	init_mlx_image(data);
	init_plane_data(data);
	calculate_map_dimensions(data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}