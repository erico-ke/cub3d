/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:17:37 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/25 17:30:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, int x)
{
	ray->camerax = 2 * x / (double)SCREEN_W - 1;
	ray->raydirx = player->dir_x + player->plane_x * ray->camerax;
	ray->raydiry = player->dir_y + player->plane_y * ray->camerax;
	ray->mapx = (int)player->x_uni;
	ray->mapy = (int)player->y_uni;
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (player->x_uni - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - player->x_uni) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (player->y_uni - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - player->y_uni) * ray->deltadisty;
	}
}

void	perform_dda(t_ray *ray, char **map)
{
	int	max_iterations;

	max_iterations = 0;
	while (ray->hit == 0 && max_iterations < 1000)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapy < 0 || !map[ray->mapy] || ray->mapx < 0
			|| !map[ray->mapy][ray->mapx] || map[ray->mapy][ray->mapx] == ' '
			|| map[ray->mapy][ray->mapx] == '\n'
			|| map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
		max_iterations++;
	}
}

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

void	cast_single_ray(t_data *data, int x)
{
	t_ray	ray;

	init_ray(&ray, data->player, x);
	calculate_step_and_side_dist(&ray, data->player);
	perform_dda(&ray, data->map);
	calculate_wall_distance(&ray, data->player);
	draw_vertical_line(data, x, &ray);
}
