/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:55:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/08 21:55:21 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_textures(t_plane *plane)
{
	if (!plane->no_texture)
		return (ft_printf("Error: Missing North texture (NO)\n"), 0);
	if (!plane->so_texture)
		return (ft_printf("Error: Missing South texture (SO)\n"), 0);
	if (!plane->we_texture)
		return (ft_printf("Error: Missing West texture (WE)\n"), 0);
	if (!plane->ea_texture)
		return (ft_printf("Error: Missing East texture (EA)\n"), 0);
	return (1);
}

int	check_colors(t_plane *plane)
{
	if (plane->f_red < 0 || plane->f_red > 255
		|| plane->f_green < 0 || plane->f_green > 255
		|| plane->f_blue < 0 || plane->f_blue > 255)
		return (ft_printf("Error: Invalid Floor color\n"), 0);
	if (plane->c_red < 0 || plane->c_red > 255
		|| plane->c_green < 0 || plane->c_green > 255
		|| plane->c_blue < 0 || plane->c_blue > 255)
		return (ft_printf("Error: Invalid Ceiling color\n"), 0);
	return (1);
}

int	check_config(t_plane *plane)
{
	if (!check_textures(plane))
		return (0);
	if (!check_colors(plane))
		return (0);
	return (1);
}
