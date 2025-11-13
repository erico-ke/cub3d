/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42malaga.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:30:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:30:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Parse textures & colors.
int	parse_textures_n_colors(char **lines, t_data *data)
{
	(void)lines;
	(void)data;
	// TODO: Implementar parser de texturas y colores
	return (0);
}

//Check walls(walls has to be around all the map as delimiters)
int	check_walls(char **map)
{
	(void)map;
	// TODO: Implementar validación de paredes
	return (0);
}

//Check instances(check if we have all the things to start our game)
int	check_instances(char **map)
{
	(void)map;
	// TODO: Implementar validación de instancias
	return (0);
}

//Check if there is an exitent exit path to complete the game.
int	check_exit_path(char **map)
{
	(void)map;
	// TODO: Implementar validación de camino de salida
	return (0);
}

//Free the map memory
void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}