/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/11 15:14:58 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	check_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return ('\0');
}

static char	set_player_pos(t_data *data, int i, int j)
{
	char	orientation;

	orientation = data->map[i][j];
	data->player->x_uni = (double)j + 0.5;
	data->player->y_uni = (double)i + 0.5;
	data->player->x = j;
	data->player->y = i;
	data->map[i][j] = '0';
	return (orientation);
}

static char	find_player_position(t_data *data)
{
	int		i;
	int		j;
	char	orientation;

	i = 0;
	orientation = '\0';
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (check_player_char(data->map[i][j]))
				return (set_player_pos(data, i, j));
			j++;
		}
		i++;
	}
	return (orientation);
}

void	init_player(t_data *data)
{
	char	orientation;

	if (!data->player)
	{
		data->player = malloc(sizeof(t_player));
		if (!data->player)
		{
			perror("Error: player not initialized");
			mlx_close_window(data->mlx);
			cleanup_data(data);
			exit(EXIT_FAILURE);
		}
	}
	orientation = find_player_position(data);
	set_player_direction(data->player, orientation);
}

void	calculate_map_dimensions(t_data *data)
{
	int	i;
	int	len;

	data->map_height = 0;
	data->map_width = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > data->map_width)
			data->map_width = len;
		data->map_height++;
		i++;
	}
}
