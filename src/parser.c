/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/08 22:13:18 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Read Map.cub & filters textures and map
int	read_cub(const char *filecub, t_data *data)
{
	int		fd;
	char	*line;
	char	*map_content;

	fd = open(filecub, O_RDONLY);
	map_content = NULL;
	if (fd < 0)
		return (ft_printf("Error opening file\n"), 1);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == ' ' || line[0] == '\t' || ft_isdigit(line[0])
			|| line[0] == '1')
		{
			map_content = ft_strjoin_g(map_content, line);
		}
		else
			textures_n_colors(line, data, NULL);
		free(line);
	}
	close(fd);
	if (!map_content)
		return (ft_printf("No map found in file\n"), 1);
	data->map = ft_split(map_content, '\n');
	free(map_content);
	return (1);
}

//Parse textures & colors.
void	textures_n_colors(char *line, t_data *data, char **rgb)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->plane->NO_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->plane->SO_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->plane->WE_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->plane->EA_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		rgb = ft_split(line + 2, ',');
		data->plane->F_red = ft_atoi(rgb[0]);
		data->plane->F_green = ft_atoi(rgb[1]);
		data->plane->F_blue = ft_atoi(rgb[2]);
		free_map(rgb);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		rgb = ft_split(line + 2, ',');
		data->plane->C_red = ft_atoi(rgb[0]);
		data->plane->C_green = ft_atoi(rgb[1]);
		data->plane->C_blue = ft_atoi(rgb[2]);
		free_map(rgb);
	}
}
//Converts int to uint32_t
void	parse_color(t_plane *plane)
{
	plane->ccolor = (plane->C_red << 24) | (plane->C_green << 16)
		| (plane->C_blue << 8) | 255;
	plane->fcolor = (plane->F_red << 24) | (plane->F_green << 16)
		| (plane->F_blue << 8) | 255;
}

//Check_perimeter(walls(1) or spaces has to be around all the map as delimiters)
int	check_perimeter(char **map)
{
	int	i;
	int	lline;
	char	last;

	i = 0;
	last = '\0';
	if (!map)
		return (0);
	while(map[i])
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
int	check_player(char **map, t_player *player, int i, int j)
{
	int	count;
	int	pos[2];

	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_player(map[i][j]))
			{
				count++;
				pos[0] = j;
				pos[1] = i;
			}
		}
	}
	if (count == 1)
		save_player(player, pos[0], pos[1]);
	return (count);
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

//Debug function to print map content
void	print_map_debug(char **map)
{
	int	i;

	if (!map)
	{
		ft_printf("Map is NULL\n");
		return;
	}

	ft_printf("=== MAP CONTENT DEBUG ===\n");
	i = 0;
	while (map[i])
	{
		ft_printf("Line %d: [%s]\n", i, map[i]);
		i++;
	}
	ft_printf("=== END MAP DEBUG (total %d lines) ===\n", i);
}
