/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:27:57 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/11 11:17:11 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (0);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_printf("Error: File must have .cub extension\n");
		return (0);
	}
	return (1);
}

static void	init_plane_pointers(t_plane *plane)
{
	plane->no_texture = NULL;
	plane->so_texture = NULL;
	plane->we_texture = NULL;
	plane->ea_texture = NULL;
	plane->tex_north = NULL;
	plane->tex_south = NULL;
	plane->tex_west = NULL;
	plane->tex_east = NULL;
}

static t_data	*init_data_structures(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Error allocating memory for data\n");
		return (NULL);
	}
	data->plane = malloc(sizeof(t_plane));
	if (!data->plane)
	{
		free(data);
		ft_printf("Error allocating memory for plane\n");
		return (NULL);
	}
	init_plane_pointers(data->plane);
	data->map = NULL;
	data->player = NULL;
	data->mlx = NULL;
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!validate_args(argc, argv))
		return (EXIT_FAILURE);
	data = init_data_structures();
	if (!data)
		return (EXIT_FAILURE);
	if (read_cub(argv[1], data) != 1)
	{
		cleanup_data(data);
		return (EXIT_FAILURE);
	}
	parse_color(data->plane);
	if (!check_instances(data->map, data->player, data->plane))
	{
		cleanup_data(data);
		return (EXIT_FAILURE);
	}
	init_mlx(data);
	return (EXIT_SUCCESS);
}
