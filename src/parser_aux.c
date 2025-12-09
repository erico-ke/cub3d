/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:05:15 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/08 22:08:02 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	closed_line(char *line)
{
	int	i;

	i = 0;

	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	get_first(char *line)
{
	int	i;

	i = 0;
	while(line[i] == ' ')
		i++;
	return (line[i]);
}

char	get_last(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0)
		return (line[i - 1]);
	return ('\0');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	save_player(t_player *player, int x, int y)
{
	player->x = x;
	player->y = y;
}
