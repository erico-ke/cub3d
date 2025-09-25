/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:15:03 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/25 17:31:58 by erico-ke         ###   ########.fr       */
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

void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player->x_uni + move_x;
	new_y = data->player->y_uni + move_y;

	// Verificar colisiones en X
	if (data->map[(int)data->player->y_uni][(int)new_x] != '1')
		data->player->x_uni = new_x;

	// Verificar colisiones en Y
	if (data->map[(int)new_y][(int)data->player->x_uni] != '1')
		data->player->y_uni = new_y;

	// Actualizar posiciones enteras
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
	// Movimiento hacia adelante/atrás
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, data->player->dir_x * MOVE_SPEED, data->player->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -data->player->dir_x * MOVE_SPEED, -data->player->dir_y * MOVE_SPEED);

	// Movimiento lateral (strafe)
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, data->player->plane_x * MOVE_SPEED, data->player->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, -data->player->plane_x * MOVE_SPEED, -data->player->plane_y * MOVE_SPEED);

	// Rotación horizontal de la cámara
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, ROT_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, -ROT_SPEED);
}

void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		perror("Error: player not initialized");
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	// Posición inicial del jugador (puedes ajustar estos valores)
	data->player->x_uni = 2.0;
	data->player->y_uni = 2.0;
	data->player->x = (int)data->player->x_uni;
	data->player->y = (int)data->player->y_uni;
	// Dirección inicial del jugador (mirando hacia el este)
	data->player->dir_x = 1.0;
	data->player->dir_y = 0.0;
	// Plano de la cámara (perpendicular a la dirección)
	data->player->plane_x = 0.0;
	data->player->plane_y = 0.66;
}

void	init_test_map(t_data *data)
{
	// Crear un mapa de prueba más grande
	data->map_height = 10;
	data->map_width = 10;
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		perror("Error: map not initialized");
		exit(EXIT_FAILURE);
	}
	data->map[0] = ft_strdup("1111111111");
	data->map[1] = ft_strdup("1000000001");
	data->map[2] = ft_strdup("1000000001");
	data->map[3] = ft_strdup("1000000001");
	data->map[4] = ft_strdup("1000000001");
	data->map[5] = ft_strdup("1000000001");
	data->map[6] = ft_strdup("1000000001");
	data->map[7] = ft_strdup("1000000001");
	data->map[8] = ft_strdup("1000000001");
	data->map[9] = ft_strdup("1111111111");
	data->map[10] = NULL;
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

	// Inicializar el plano (colores de cielo y suelo)
	data->plane = malloc(sizeof(t_plane));
	if (!data->plane)
	{
		perror("Error: plane not initialized");
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->plane->ccolor = 0x87CEEBFF; // Cielo azul claro
	data->plane->fcolor = 0x8B4513FF; // Suelo marrón

	// Inicializar jugador y mapa
	init_player(data);
	init_test_map(data);

	// Configurar el loop de juego
	mlx_loop_hook(data->mlx, game_loop, data);

	mlx_loop(data->mlx);
}
