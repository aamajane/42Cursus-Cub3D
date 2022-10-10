/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:45:59 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/06 23:31:28 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	map_content(t_data *data, double x, double y, int size)
{
	int	grid_x;
	int	grid_y;

	if (x < 0 || x >= data->elm.map_width * size || \
		y < 0 || y >= data->elm.map_height * size)
		return (0);
	grid_x = (int)floor(x / size);
	grid_y = (int)floor(y / size);
	return (data->elm.map[grid_y][grid_x]);
}

int	is_inside_map(t_data *data, double x, double y)
{
	if (x >= 0 && x < data->elm.map_width * TILE_SIZE && \
		y >= 0 && y < data->elm.map_height * TILE_SIZE)
		return (1);
	return (0);
}

int	is_wall(char c)
{
	if (c >= '1' && c < '1' + NUM_WALLS)
		return (c - '0');
	return (0);
}

void	random_wall(char ***map)
{
	int	i;
	int	j;

	i = -1;
	while ((*map)[++i])
	{
		j = -1;
		while ((*map)[i][++j])
			if ((*map)[i][j] == '1')
				(*map)[i][j] = (rand() % (MAX_WALL_NUM + 1 - MIN_WALL_NUM) + \
								MIN_WALL_NUM) + '0';
	}	
}

void	draw_rect(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	index;

	j = -1;
	while (++j < RECT_SIZE)
	{
		i = -1;
		while (++i < RECT_SIZE)
		{
			index = ((y + j) * data->minimap.line_length) + (x + i);
			data->minimap.buffer[index] = color;
		}
	}
}
