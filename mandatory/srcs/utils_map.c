/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:45:59 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 16:06:48 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	map_width(char **map)
{
	int	width;
	int	i;
	int	j;

	width = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > width)
			width = j;
		i++;
	}
	return (width);
}

int	map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}

int	map_has_wall_at(t_data *data, double x, double y)
{
	int	grid_x;
	int	grid_y;

	if (x < 0 || x >= data->elm.map_width * TILE_SIZE || \
		y < 0 || y >= data->elm.map_height * TILE_SIZE)
		return (1);
	grid_x = (int)floor(x / TILE_SIZE);
	grid_y = (int)floor(y / TILE_SIZE);
	if (data->elm.map[grid_y][grid_x] == '1')
		return (1);
	return (0);
}

int	is_inside_map(t_data *data, double x, double y)
{
	if (x >= 0 && x < data->elm.map_width * TILE_SIZE && \
		y >= 0 && y < data->elm.map_height * TILE_SIZE)
		return (1);
	return (0);
}
