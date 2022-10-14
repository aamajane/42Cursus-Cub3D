/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:09:48 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 15:20:47 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	sprites_number(char **map, char c)
{
	int	sprites_num;
	int	x;
	int	y;

	sprites_num = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == c)
				sprites_num++;
	}
	return (sprites_num);
}

void	sprites_coordinates(t_sprite *sprites, char **map, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == c)
			{
				sprites[i].x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				sprites[i].y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				i++;
			}
		}
	}
}

void	init_sprites_data(t_sprite *sprites, int sprites_num)
{
	int	i;

	i = -1;
	while (++i < sprites_num)
	{
		sprites[i].health = 100;
		sprites[i].on_target = 0;
		sprites[i].is_dead = 0;
	}
}
