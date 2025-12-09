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

static void	parse_textures(char *line, t_plane *plane)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		plane->no_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		plane->so_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		plane->we_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		plane->ea_texture = ft_strdup(line + 3);
}

static void	parse_floor_color(char *line, t_plane *plane)
{
	char	**rgb;

	rgb = ft_split(line + 2, ',');
	plane->f_red = ft_atoi(rgb[0]);
	plane->f_green = ft_atoi(rgb[1]);
	plane->f_blue = ft_atoi(rgb[2]);
	free_map(rgb);
}

static void	parse_ceiling_color(char *line, t_plane *plane)
{
	char	**rgb;

	rgb = ft_split(line + 2, ',');
	plane->c_red = ft_atoi(rgb[0]);
	plane->c_green = ft_atoi(rgb[1]);
	plane->c_blue = ft_atoi(rgb[2]);
	free_map(rgb);
}

void	textures_n_colors(char *line, t_data *data, char **rgb)
{
	(void)rgb;
	parse_textures(line, data->plane);
	if (ft_strncmp(line, "F ", 2) == 0)
		parse_floor_color(line, data->plane);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_ceiling_color(line, data->plane);
	parse_color(data->plane);
}

int	read_cub(const char *filecub, t_data *data)
{
	int		fd;
	char	*map_content;

	fd = open(filecub, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error opening file\n"), 1);
	map_content = read_map_lines(fd, data);
	close(fd);
	if (!map_content)
		return (ft_printf("No map found in file\n"), 1);
	data->map = ft_split(map_content, '\n');
	free(map_content);
	return (1);
}
