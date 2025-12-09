/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/09 00:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clean_texture_path(char *path)
{
	int	len;

	if (!path)
		return ;
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '
			|| path[len - 1] == '\t' || path[len - 1] == '\r'))
	{
		path[len - 1] = '\0';
		len--;
	}
}

static mlx_texture_t	*load_and_print_texture(char *path, char *name,
		t_data *data)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_printf("Error loading %s texture: %s\n", name, path);
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("✓ %s texture loaded: %dx%d (%d bpp)\n", name,
		texture->width, texture->height, texture->bytes_per_pixel * 8);
	return (texture);
}

void	load_textures(t_data *data)
{
	clean_texture_path(data->plane->no_texture);
	clean_texture_path(data->plane->so_texture);
	clean_texture_path(data->plane->we_texture);
	clean_texture_path(data->plane->ea_texture);
	data->plane->tex_north = load_and_print_texture(data->plane->no_texture,
			"North", data);
	data->plane->tex_south = load_and_print_texture(data->plane->so_texture,
			"South", data);
	data->plane->tex_west = load_and_print_texture(data->plane->we_texture,
			"West", data);
	data->plane->tex_east = load_and_print_texture(data->plane->ea_texture,
			"East", data);
}
