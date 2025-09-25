/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:27:57 by erico-ke          #+#    #+#             */
/*   Updated: 2025/09/25 17:23:46 by erico-ke         ###   ########.fr       */
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
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Error allocating memory for data");
		return (EXIT_FAILURE);
	}
	init_mlx(data);
	return (EXIT_SUCCESS);
}
