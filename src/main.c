/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:27:57 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 16:01:53 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	// Verificar que el archivo tenga extensión .cub
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_printf("Error: File must have .cub extension\n");
		return (EXIT_FAILURE);
	}

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Error allocating memory for data\n");
		return (EXIT_FAILURE);
	}

	// Leer y parsear el mapa antes de inicializar MLX
	if (read_map(argv[1], data) != 0)
	{
		free(data);
		return (EXIT_FAILURE);
	}

	// Inicializar estructura del jugador
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		ft_printf("Error allocating memory for player\n");
		free_map(data->map);
		free(data);
		return (EXIT_FAILURE);
	}

	// Buscar posición y orientación del jugador en el mapa
	if (find_player_position(data->map, data->player) != 0)
	{
		free(data->player);
		free_map(data->map);
		free(data);
		return (EXIT_FAILURE);
	}

	init_mlx(data);
	return (EXIT_SUCCESS);
}
