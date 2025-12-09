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
	if (!plane->NO_texture)
		return (ft_printf("Error: Missing North texture (NO)\n"), 0);
	if (!plane->SO_texture)
		return (ft_printf("Error: Missing South texture (SO)\n"), 0);
	if (!plane->WE_texture)
		return (ft_printf("Error: Missing West texture (WE)\n"), 0);
	if (!plane->EA_texture)
		return (ft_printf("Error: Missing East texture (EA)\n"), 0);
	return (1);
}

int	check_colors(t_plane *plane)
{
	if (plane->F_red < 0 || plane->F_red > 255
		|| plane->F_green < 0 || plane->F_green > 255
		|| plane->F_blue < 0 || plane->F_blue > 255)
		return (ft_printf("Error: Invalid Floor color\n"), 0);
	if (plane->C_red < 0 || plane->C_red > 255
		|| plane->C_green < 0 || plane->C_green > 255
		|| plane->C_blue < 0 || plane->C_blue > 255)
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
