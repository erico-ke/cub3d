/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@student.42malaga.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/11/12 17:00:00 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Count players in the map (N, S, E, W characters)
int	count_players_in_map(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

//Set direction for North and South orientations
static void	set_ns_orientation(t_player *player, char orientation)
{
	if (orientation == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (orientation == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

//Set direction for East and West orientations
static void	set_ew_orientation(t_player *player, char orientation)
{
	if (orientation == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (orientation == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

//Set player orientation based on the character found (N, S, E, W)
void	set_player_orientation(t_player *player, char orientation)
{
	if (orientation == 'N' || orientation == 'S')
		set_ns_orientation(player, orientation);
	else if (orientation == 'E' || orientation == 'W')
		set_ew_orientation(player, orientation);
}



