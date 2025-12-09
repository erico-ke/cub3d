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
	while (line[i] == ' ')
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

int	check_perimeter(char **map)
{
	int		i;
	int		lline;
	char	last;

	i = 0;
	last = '\0';
	if (!map)
		return (0);
	while (map[i])
		i++;
	lline = i - 1;
	i = 0;
	if (!closed_line(map[0]) || !closed_line(map[lline]))
		return (0);
	while (map[i])
	{
		if (get_first(map[i]) != '1')
			return (0);
		last = get_last(map[i]);
		if (last == '\0' || (last != '1' && last != ' '))
			return (0);
		i++;
	}
	return (1);
}
