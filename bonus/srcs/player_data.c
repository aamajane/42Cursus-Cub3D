/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:02:26 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 03:06:21 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	player_data(t_player *player, char **map)
{
	double	start_angle;

	start_angle = player_position(player, map);
	player->rot_angle = degree_to_radian(start_angle);
	player->fov_angle = degree_to_radian(60);
	player->rot_speed = degree_to_radian(2);
	player->mov_speed = 3;
	player->rot_direction = 0;
	player->mov_direction = 0;
}

double	player_position(t_player *player, char **map)
{
	double	start_angle;
	int		x;
	int		y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_player(map[y][x]))
			{
				player->x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				player->y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				start_angle = player_starting_angle(map[y][x]);
				map[y][x] = '0';
				return (start_angle);
			}
		}
	}
	return (0);
}

double	player_starting_angle(char c)
{
	if (c == 'N')
		return (270);
	else if (c == 'S')
		return (90);
	else if (c == 'E')
		return (0);
	else if (c == 'W')
		return (180);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
