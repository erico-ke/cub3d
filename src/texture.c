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
	// Eliminar espacios en blanco y newlines al final
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' ' 
		|| path[len - 1] == '\t' || path[len - 1] == '\r'))
	{
		path[len - 1] = '\0';
		len--;
	}
}

void	load_textures(t_data *data)
{
	// Limpiar rutas de texturas
	clean_texture_path(data->plane->NO_texture);
	clean_texture_path(data->plane->SO_texture);
	clean_texture_path(data->plane->WE_texture);
	clean_texture_path(data->plane->EA_texture);

	// Cargar texturas
	data->plane->tex_north = mlx_load_png(data->plane->NO_texture);
	if (!data->plane->tex_north)
	{
		ft_printf("Error loading North texture: %s\n", data->plane->NO_texture);
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("✓ North texture loaded: %dx%d (%d bpp)\n", 
		data->plane->tex_north->width, data->plane->tex_north->height,
		data->plane->tex_north->bytes_per_pixel * 8);

	data->plane->tex_south = mlx_load_png(data->plane->SO_texture);
	if (!data->plane->tex_south)
	{
		ft_printf("Error loading South texture: %s\n", data->plane->SO_texture);
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("✓ South texture loaded: %dx%d (%d bpp)\n",
		data->plane->tex_south->width, data->plane->tex_south->height,
		data->plane->tex_south->bytes_per_pixel * 8);

	data->plane->tex_west = mlx_load_png(data->plane->WE_texture);
	if (!data->plane->tex_west)
	{
		ft_printf("Error loading West texture: %s\n", data->plane->WE_texture);
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("✓ West texture loaded: %dx%d (%d bpp)\n",
		data->plane->tex_west->width, data->plane->tex_west->height,
		data->plane->tex_west->bytes_per_pixel * 8);

	data->plane->tex_east = mlx_load_png(data->plane->EA_texture);
	if (!data->plane->tex_east)
	{
		ft_printf("Error loading East texture: %s\n", data->plane->EA_texture);
		mlx_close_window(data->mlx);
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	ft_printf("✓ East texture loaded: %dx%d (%d bpp)\n",
		data->plane->tex_east->width, data->plane->tex_east->height,
		data->plane->tex_east->bytes_per_pixel * 8);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*pixel;
	uint32_t	color;
	int			index;

	// Asegurarse de que las coordenadas estén dentro de los límites usando módulo
	// Esto permite texturas de cualquier tamaño
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= (int)texture->width)
		x = x % texture->width;
	if (y >= (int)texture->height)
		y = y % texture->height;

	// Calcular índice del píxel en el array de bytes
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	
	// Obtener el píxel de la textura
	pixel = &texture->pixels[index];
	
	// Convertir de RGBA a formato MLX42 (RGBA little endian)
	// MLX42 usa: RGBA donde cada byte es R, G, B, A
	if (texture->bytes_per_pixel == 4)
	{
		// RGBA completo
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	}
	else if (texture->bytes_per_pixel == 3)
	{
		// RGB sin alpha - agregar alpha opaco
		color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF;
	}
	else
	{
		// Formato no soportado - devolver magenta
		color = 0xFF00FFFF;
	}
	
	return (color);
}
