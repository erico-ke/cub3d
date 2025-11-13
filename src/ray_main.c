/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42malaga.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:30:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:30:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_single_ray(t_data *data, int x)
{
	t_ray	ray;

	init_ray(&ray, data->player, x);
	calculate_step_and_side_dist(&ray, data->player);
	perform_dda(&ray, data->map);
	calculate_wall_distance(&ray, data->player);
	draw_vertical_line(data, x, &ray);
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