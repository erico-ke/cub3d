/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 00:00:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/12/11 15:38:39 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	print_map_debug(char **map)
{
	int	i;

	if (!map)
	{
		ft_printf("Map is NULL\n");
		return ;
	}
	ft_printf("=== MAP CONTENT DEBUG ===\n");
	i = 0;
	while (map[i])
	{
		ft_printf("Line %d: [%s]\n", i, map[i]);
		i++;
	}
	ft_printf("========================\n");
}

void	parse_color(t_plane *plane)
{
	plane->ccolor = (plane->c_red << 24) | (plane->c_green << 16)
		| (plane->c_blue << 8) | 255;
	plane->fcolor = (plane->f_red << 24) | (plane->f_green << 16)
		| (plane->f_blue << 8) | 255;
}

char	*read_map_lines(int fd, t_data *data)
{
	char	*line;
	char	*map_content;

	map_content = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == ' ' || line[0] == '\t' || ft_isdigit(line[0])
			|| line[0] == '1')
			map_content = ft_strjoin_g(map_content, line);
		else if (!textures_n_colors(line, data, NULL))
			return (free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (map_content);
}
