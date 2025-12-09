/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/09 00:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

mlx_texture_t	*select_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			return (data->plane->tex_east);
		else
			return (data->plane->tex_west);
	}
	else
	{
		if (ray->raydiry > 0)
			return (data->plane->tex_south);
		else
			return (data->plane->tex_north);
	}
}

void	calculate_texture_x(t_ray *ray, t_player *player,
	mlx_texture_t *texture)
{
	if (ray->side == 0)
		ray->wallx = player->y_uni + ray->perpwalldist * ray->raydiry;
	else
		ray->wallx = player->x_uni + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * (double)texture->width);
	if ((ray->side == 0 && ray->raydirx > 0)
		|| (ray->side == 1 && ray->raydiry < 0))
		ray->texx = texture->width - ray->texx - 1;
}
