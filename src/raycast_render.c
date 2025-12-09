/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/09 00:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	calc_texture_step(mlx_texture_t *texture, t_ray *ray,
				double *step, double *texpos)
{
	*step = 1.0 * texture->height / ray->lineheight;
	*texpos = (ray->drawstart - SCREEN_H / 2 + ray->lineheight / 2) * (*step);
}

static void	render_textured_line(t_data *data, int x, t_ray *ray,
				mlx_texture_t *texture)
{
	int			y;
	uint32_t	color;
	int			texy;
	double		step;
	double		texpos;

	calc_texture_step(texture, ray, &step, &texpos);
	y = ray->drawstart;
	while (y <= ray->drawend)
	{
		texy = (int)texpos;
		if (texy < 0)
			texy = 0;
		else if (texy >= (int)texture->height)
			texy = texy % texture->height;
		texpos += step;
		color = get_texture_color(texture, ray->texx, texy);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F7F;
		mlx_put_pixel(data->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	mlx_texture_t	*texture;

	texture = select_texture(data, ray);
	calculate_texture_x(ray, data->player, texture);
	render_textured_line(data, x, ray, texture);
}

void	clear_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			if (y < SCREEN_H / 2)
				mlx_put_pixel(data->img, x, y, data->plane->ccolor);
			else
				mlx_put_pixel(data->img, x, y, data->plane->fcolor);
			x++;
		}
		y++;
	}
}

void	render_frame(t_data *data)
{
	int	x;

	clear_background(data);
	x = 0;
	while (x < SCREEN_W)
	{
		cast_single_ray(data, x);
		x++;
	}
}
