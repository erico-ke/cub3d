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

static int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		ft_printf("Error: File must have .cub extension\n");
		return (1);
	}
	return (0);
}

static t_data	*allocate_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Error allocating memory for data\n");
		return (NULL);
	}
	return (data);
}

static int	init_player_data(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		ft_printf("Error allocating memory for player\n");
		return (1);
	}
	if (find_player_position(data->map, data->player) != 0)
	{
		free(data->player);
		return (1);
	}
	return (0);
}

static void	cleanup_and_exit(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->player)
			free(data->player);
		if (data->map)
			free_map(data->map);
		free(data);
	}
	exit(exit_code);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (validate_arguments(argc, argv) != 0)
		return (EXIT_FAILURE);
	data = allocate_data();
	if (!data)
		return (EXIT_FAILURE);
	if (read_map(argv[1], data) != 0)
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (init_player_data(data) != 0)
		cleanup_and_exit(data, EXIT_FAILURE);
	init_mlx(data);
	return (EXIT_SUCCESS);
}
