/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42malaga.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Check if character is a player character
static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

//Set player position and orientation from map coordinates
static int	set_player_from_position(char **map, t_player *player, int i, int j)
{
	player->x = j;
	player->y = i;
	player->x_uni = (double)j + 0.5;
	player->y_uni = (double)i + 0.5;
	set_player_orientation(player, map[i][j]);
	map[i][j] = '0';
	return (0);
}

//Search for player character in the map
int	search_player_in_map(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
				return (set_player_from_position(map, player, i, j));
			j++;
		}
		i++;
	}
	return (1);
}

//Find player position and orientation in the map
int	find_player_position(char **map, t_player *player)
{
	int	player_count;

	player_count = count_players_in_map(map);
	if (player_count != 1)
	{
		ft_printf("Error\nMap must contain exactly one player ");
		ft_printf("(N,S,E,W). Found: %d\n", player_count);
		return (1);
	}
	return (search_player_in_map(map, player));
}