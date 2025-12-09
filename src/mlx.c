/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:03 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:19:30 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup_data(t_data *data)
{
	if (!data)
		return ;
	
	// Liberar mapa
	if (data->map)
		free_map(data->map);
	
	// Liberar plane y sus strings
	if (data->plane)
	{
		if (data->plane->NO_texture)
			free(data->plane->NO_texture);
		if (data->plane->SO_texture)
			free(data->plane->SO_texture);
		if (data->plane->WE_texture)
			free(data->plane->WE_texture);
		if (data->plane->EA_texture)
			free(data->plane->EA_texture);
		
		// Liberar texturas MLX (si MLX está inicializado)
		if (data->mlx)
		{
			if (data->plane->tex_north)
				mlx_delete_texture(data->plane->tex_north);
			if (data->plane->tex_south)
				mlx_delete_texture(data->plane->tex_south);
			if (data->plane->tex_west)
				mlx_delete_texture(data->plane->tex_west);
			if (data->plane->tex_east)
				mlx_delete_texture(data->plane->tex_east);
		}
		
		free(data->plane);
	}
	
	// Liberar player
	if (data->player)
		free(data->player);
	
	// Liberar data
	free(data);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_SUCCESS);
	}
}

void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x_uni + move_x;
	new_y = data->player->y_uni + move_y;
	if (data->map[(int)data->player->y_uni][(int)new_x] != '1')
		data->player->x_uni = new_x;
	if (data->map[(int)new_y][(int)data->player->x_uni] != '1')
		data->player->y_uni = new_y;
	data->player->x = (int)data->player->x_uni;
	data->player->y = (int)data->player->y_uni;
}

void	rotate_player(t_data *data, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->dir_x;
	data->player->dir_x = data->player->dir_x * cos(rot) - data->player->dir_y * sin(rot);
	data->player->dir_y = old_dir_x * sin(rot) + data->player->dir_y * cos(rot);

	old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x * cos(rot) - data->player->plane_y * sin(rot);
	data->player->plane_y = old_plane_x * sin(rot) + data->player->plane_y * cos(rot);
}

void	handle_movement(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, data->player->dir_x * MOVE_SPEED, data->player->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -data->player->dir_x * MOVE_SPEED, -data->player->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, data->player->plane_x * MOVE_SPEED, data->player->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, -data->player->plane_x * MOVE_SPEED, -data->player->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, ROT_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, -ROT_SPEED);
}

void	set_player_direction(t_player *player, char orientation)
{
	if (orientation == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (orientation == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (orientation == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (orientation == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

void	init_player(t_data *data)
{
	int	i;
	int	j;
	char	orientation;

	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		perror("Error: player not initialized");
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	// Buscar posición del jugador en el mapa
	i = 0;
	orientation = '\0';
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
				data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				orientation = data->map[i][j];
				data->player->x_uni = (double)j + 0.5;
				data->player->y_uni = (double)i + 0.5;
				data->player->x = j;
				data->player->y = i;
				// Reemplazar con '0' para que el raycaster lo vea como espacio vacío
				data->map[i][j] = '0';
				break;
			}
			j++;
		}
		if (orientation != '\0')
			break;
		i++;
	}
	// Configurar dirección según orientación
	set_player_direction(data->player, orientation);
}

void	calculate_map_dimensions(t_data *data)
{
	int	i;
	int	len;

	data->map_height = 0;
	data->map_width = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		// Remover newline si existe
		if (len > 0 && data->map[i][len - 1] == '\n')
			len--;
		if (len > data->map_width)
			data->map_width = len;
		data->map_height++;
		i++;
	}
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_movement(data);
	render_frame(data);
}

void	init_mlx(t_data *data)
{
	ft_printf("Attempting to initialize MLX...\n");
	data->mlx = mlx_init(SCREEN_W, SCREEN_H, "Cub3D", true);
	if (!data->mlx)
	{
		ft_printf("MLX initialization failed!\n");
		perror("Error initializing MLX");
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("MLX initialized successfully!\n");
	mlx_key_hook(data->mlx, &handle_keypress, data);
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	if (!data->img)
	{
		perror("Error creating image");
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	// data->plane ya fue inicializado y llenado por el parser en main.c
	// Los colores ya están configurados en data->plane->ccolor y fcolor
	load_textures(data);
	calculate_map_dimensions(data);
	init_player(data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}