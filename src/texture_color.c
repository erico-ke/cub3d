/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/09 00:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clamp_texture_coords(int *x, int *y, mlx_texture_t *texture)
{
	if (*x < 0)
		*x = 0;
	if (*y < 0)
		*y = 0;
	if (*x >= (int)texture->width)
		*x = *x % texture->width;
	if (*y >= (int)texture->height)
		*y = *y % texture->height;
}

static uint32_t	pixel_to_color(uint8_t *pixel, int bytes_per_pixel)
{
	uint32_t	color;

	if (bytes_per_pixel == 4)
		color = (pixel[0] << 24) | (pixel[1] << 16)
			| (pixel[2] << 8) | pixel[3];
	else if (bytes_per_pixel == 3)
		color = (pixel[0] << 24) | (pixel[1] << 16)
			| (pixel[2] << 8) | 0xFF;
	else
		color = 0xFF00FFFF;
	return (color);
}

uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*pixel;
	int		index;

	clamp_texture_coords(&x, &y, texture);
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	pixel = &texture->pixels[index];
	return (pixel_to_color(pixel, texture->bytes_per_pixel));
}
