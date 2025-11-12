/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/11/12 16:34:12 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Check if a line is a map line (contains only valid map characters)
int	is_map_line(char *line)
{
	int	i;

	if (!line || !*line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

//Extract only the map lines from the full file content
char	**extract_map_lines(char **all_lines)
{
	char	**map_lines;
	int		i;
	int		j;
	int		map_start;
	int		map_count;

	// Find first map line
	i = 0;
	map_start = -1;
	while (all_lines[i])
	{
		if (is_map_line(all_lines[i]))
		{
			map_start = i;
			break;
		}
		i++;
	}
	if (map_start == -1)
		return (NULL);
	
	// Count map lines
	map_count = 0;
	i = map_start;
	while (all_lines[i] && is_map_line(all_lines[i]))
	{
		map_count++;
		i++;
	}
	
	// Copy map lines
	map_lines = malloc(sizeof(char *) * (map_count + 1));
	if (!map_lines)
		return (NULL);
	j = 0;
	i = map_start;
	while (j < map_count)
	{
		map_lines[j] = ft_strdup(all_lines[i]);
		j++;
		i++;
	}
	map_lines[j] = NULL;
	return (map_lines);
}

//Read Map.cub & keep it into data->map
int	read_map(const char *filecub, t_data *data)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	**all_lines;

	fd = open(filecub, O_RDONLY);
	tmp = NULL;
	if (fd < 0)
		return (ft_printf("Error opening file\n"), 1);
	while ((line = get_next_line(fd)))
	{
		tmp = ft_strjoin_g(tmp, line);
		free(line);
	}
	close(fd);
	if (!tmp)
		return (ft_printf("Empty file or invalid file\n"), 1);
	all_lines = ft_split(tmp, '\n');
	free(tmp);
	
	// Extract only map lines (ignore config lines)
	data->map = extract_map_lines(all_lines);
	free_map(all_lines);
	
	if (!data->map)
		return (ft_printf("Error: No valid map found in file\n"), 1);
	return (0);
}

//Parse textures & colors.
int	parse_textures_n_colors(char **lines, t_data *data)
{
	(void)lines;
	(void)data;
	// TODO: Implementar parser de texturas y colores
	return (0);
}

//Check walls(walls has to be around all the map as delimiters)
int	check_walls(char **map)
{
	(void)map;
	// TODO: Implementar validación de paredes
	return (0);
}

//Check instances(check if we have all the things to start our game)
int	check_instances(char **map)
{
	(void)map;
	// TODO: Implementar validación de instancias
	return (0);
}

//Check if there is an exitent exit path to complete the game.
int	check_exit_path(char **map)
{
	(void)map;
	// TODO: Implementar validación de camino de salida
	return (0);
}

//Free the map memory
void	free_map(char **map)
{
	int	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

