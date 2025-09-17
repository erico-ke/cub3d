/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:05:15 by fracurul          #+#    #+#             */
/*   Updated: 2025/09/17 18:06:24 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//extract map from .cub.
char	**extract_map(char **lines)

//Check if the map have all the things needed to be playeable.
int	validate_map(char **map, t_data *data)