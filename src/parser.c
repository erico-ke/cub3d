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

//Find the start index of map lines
static int	find_map_start(char **all_lines)
{
	int	i;

	i = 0;
	while (all_lines[i])
	{
		if (is_map_line(all_lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

//Count the number of consecutive map lines
static int	count_map_lines(char **all_lines, int map_start)
{
	int	map_count;
	int	i;

	map_count = 0;
	i = map_start;
	while (all_lines[i] && is_map_line(all_lines[i]))
	{
		map_count++;
		i++;
	}
	return (map_count);
}

//Copy map lines to new array
static char	**copy_map_lines(char **all_lines, int map_start, int map_count)
{
	char	**map_lines;
	int		i;
	int		j;

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

//Extract only the map lines from the full file content
char	**extract_map_lines(char **all_lines)
{
	int	map_start;
	int	map_count;

	map_start = find_map_start(all_lines);
	if (map_start == -1)
		return (NULL);
	map_count = count_map_lines(all_lines, map_start);
	return (copy_map_lines(all_lines, map_start, map_count));
}

//Read Map.cub & keep it into data->map
//Read all lines from file into a single string
static char	*read_file_content(int fd)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	while ((line = get_next_line(fd)))
	{
		tmp = ft_strjoin_g(tmp, line);
		free(line);
	}
	return (tmp);
}

//Process file content and extract map
static int	process_file_content(char *file_content, t_data *data)
{
	char	**all_lines;

	if (!file_content)
		return (ft_printf("Empty file or invalid file\n"), 1);
	all_lines = ft_split(file_content, '\n');
	free(file_content);
	data->map = extract_map_lines(all_lines);
	free_map(all_lines);
	if (!data->map)
		return (ft_printf("Error: No valid map found in file\n"), 1);
	return (0);
}

int	read_map(const char *filecub, t_data *data)
{
	int		fd;
	char	*file_content;

	fd = open(filecub, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error opening file\n"), 1);
	file_content = read_file_content(fd);
	close(fd);
	return (process_file_content(file_content, data));
}



