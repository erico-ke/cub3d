/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 20:39:19 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/08 21:56:38 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_playable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	valid_zone(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	check_zone(char **map, int i, int j)
{
	if (i == 0 || !map[i - 1][j] || !valid_zone(map[i - 1][j]))
		return (0);
	if (!map[i + 1] || !map[i + 1][j] || !valid_zone(map[i + 1][j]))
		return (0);
	if (j == 0 || !map[i][j - 1] || !valid_zone(map[i][j - 1]))
		return (0);
	if (!map[i][j + 1] || map[i][j + 1] == '\n' || !valid_zone(map[i][j + 1]))
		return (0);
	return (1);
}

int	check_hole(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_playable(map[i][j]))
			{
				if (!check_zone(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_instances(char **map, t_player *player, t_plane *plane)
{
	if (!check_perimeter(map))
		return (printf("Perimeter is not delimited"), 0);
	if (check_player(map, player, -1, -1) != 1)
		return (printf("There is non or more than 1, player"), 0);
	if (!check_hole(map))
		return (printf("There is hole on the map, player"), 0);
	if (!check_config(plane))
		return (0);
	return (1);
}
