/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/09 00:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_textures(t_plane *plane, mlx_t *mlx)
{
	if (plane->tex_north)
		mlx_delete_texture(plane->tex_north);
	if (plane->tex_south)
		mlx_delete_texture(plane->tex_south);
	if (plane->tex_west)
		mlx_delete_texture(plane->tex_west);
	if (plane->tex_east)
		mlx_delete_texture(plane->tex_east);
	if (plane->no_texture)
		free(plane->no_texture);
	if (plane->so_texture)
		free(plane->so_texture);
	if (plane->we_texture)
		free(plane->we_texture);
	if (plane->ea_texture)
		free(plane->ea_texture);
	(void)mlx;
}

static void	free_plane_data(t_plane *plane, mlx_t *mlx)
{
	if (!plane)
		return ;
	free_textures(plane, mlx);
	free(plane);
}

void	cleanup_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		free_map(data->map);
	if (data->plane)
		free_plane_data(data->plane, data->mlx);
	if (data->player)
		free(data->player);
	if (data->mlx)
		mlx_terminate(data->mlx);
	free(data);
}

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_movement(data);
	render_frame(data);
}
