/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:27:57 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/08 22:03:48 by fracurul         ###   ########.fr       */
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

	// Inicializar la estructura plane
	data->plane = malloc(sizeof(t_plane));
	if (!data->plane)
	{
		free(data);
		ft_printf("Error allocating memory for plane\n");
		return (EXIT_FAILURE);
	}
	
	// Inicializar punteros a NULL para cleanup seguro
	data->plane->NO_texture = NULL;
	data->plane->SO_texture = NULL;
	data->plane->WE_texture = NULL;
	data->plane->EA_texture = NULL;
	data->plane->tex_north = NULL;
	data->plane->tex_south = NULL;
	data->plane->tex_west = NULL;
	data->plane->tex_east = NULL;
	data->map = NULL;
	data->player = NULL;
	data->mlx = NULL;

	// Leer y parsear el archivo .cub completo
	if (read_cub(argv[1], data) != 1)
	{
		cleanup_data(data);
		return (EXIT_FAILURE);
	}

	// Convertir colores RGB a formato RGBA
	parse_color(data->plane);

	// DEBUG: Descomentar para ver información del mapa
	// print_map_debug(data->map);
	// ft_printf("Textures: NO=[%s] SO=[%s] WE=[%s] EA=[%s]\n",
	//     data->plane->NO_texture, data->plane->SO_texture,
	//     data->plane->WE_texture, data->plane->EA_texture);
	// ft_printf("Colors: Floor=0x%X Ceiling=0x%X\n",
	//     data->plane->fcolor, data->plane->ccolor);

	init_mlx(data);
	return (EXIT_SUCCESS);
}
