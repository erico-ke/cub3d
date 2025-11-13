/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42malaga.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:30:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:30:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - player->x_uni
				+ (1 - ray->stepx) / 2) / ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - player->y_uni
				+ (1 - ray->stepy) / 2) / ray->raydiry;
	ray->lineheight = (int)(SCREEN_H / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + SCREEN_H / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + SCREEN_H / 2;
	if (ray->drawend >= SCREEN_H)
		ray->drawend = SCREEN_H - 1;
}

uint32_t	get_wall_color(t_ray *ray)
{
	uint32_t	color;

	if (ray->side == 1)
	{
		if (ray->stepy > 0)
			color = 0xFF5555FF;
		else
			color = 0x55FF55FF;
	}
	else
	{
		if (ray->stepx > 0)
			color = 0x5555FFFF;
		else
			color = 0xFFFF55FF;
	}
	if (ray->side == 1)
		color = (color >> 1) & 0x7F7F7F7F;
	return (color);
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	int			y;
	uint32_t	color;

	color = get_wall_color(ray);
	y = ray->drawstart;
	while (y <= ray->drawend)
	{
		mlx_put_pixel(data->img, x, y, color);
		y++;
	}
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