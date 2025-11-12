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

//Read Map.cub & keep it into data->map
int	read_map(const char *filecub, t_data *data)
{
	int		fd;
	char	*line;
	char	*tmp;

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
	data->map = ft_split(tmp, '\n');
	free(tmp);
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