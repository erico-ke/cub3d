/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42malaga.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	data->player->dir_x = data->player->dir_x * cos(rot) -
		data->player->dir_y * sin(rot);
	data->player->dir_y = old_dir_x * sin(rot) + data->player->dir_y * cos(rot);

	old_plane_x = data->player->plane_x;
	data->player->plane_x = data->player->plane_x * cos(rot) -
		data->player->plane_y * sin(rot);
	data->player->plane_y = old_plane_x * sin(rot) +
		data->player->plane_y * cos(rot);
}

void	handle_movement(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, data->player->dir_x * MOVE_SPEED,
			data->player->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, -data->player->dir_x * MOVE_SPEED,
			-data->player->dir_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, data->player->plane_x * MOVE_SPEED,
			data->player->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, -data->player->plane_x * MOVE_SPEED,
			-data->player->plane_y * MOVE_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, ROT_SPEED);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, -ROT_SPEED);
}