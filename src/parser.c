/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:00:00 by fracurul          #+#    #+#             */
/*   Updated: 2025/09/17 19:25:57 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Read Map.cub & keep it into data->map //right now this funct is a prototype(it does not work)
char	**read_map(const char *filecub, int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	tmp = NULL;
	if (!line)
		return (free(line), error_msg("Reading error"), 1);
	while (line)
	{
		tmp = gnl_strjoin(tmp, line);
		free(line);
		line = get_next_line(fd);
	}
	line = tmp;
	while(*line)
	{
		if(*line == '\n' && (*(line + 1) == '\n'))
			return (free(tmp), error_msg("Wrong map format"), 1);
		line++;
	}
	game->map = ft_split(tmp, '\n');
	return (free(tmp), 0);
}

//Parse textures & colors.
char	parse_textures_n_colors(char **lines, t_data *data)

//Check walls(walls has to be around all the map as delimiters)
int	check_walls(char **map)

//Check instances(check if we have all the things to start our game)
int	check_instances(char **map)

//Check if there is an exitent exit path to complete the game.
int	check_exit_path(char **map)
