/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/12/11 15:40:07 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_textures(char *line, t_plane *plane)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (plane->no_texture)
			return (0);
		plane->no_texture = ft_strdup(line + 3);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (plane->so_texture)
			return (0);
		plane->so_texture = ft_strdup(line + 3);
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (plane->we_texture)
			return (0);
		plane->we_texture = ft_strdup(line + 3);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (plane->ea_texture)
			return (0);
		plane->ea_texture = ft_strdup(line + 3);
	}
	return (1);
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

int	textures_n_colors(char *line, t_data *data, char **rgb)
{
	(void)rgb;
	if (!parse_textures(line, data->plane))
		return (ft_printf("Duplicated texture.\n"), 0);
	if (ft_strncmp(line, "F ", 2) == 0)
		parse_floor_color(line, data->plane);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_ceiling_color(line, data->plane);
	parse_color(data->plane);
	return (1);
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
