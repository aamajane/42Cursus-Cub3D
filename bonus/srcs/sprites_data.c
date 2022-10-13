/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:14:22 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/08 21:29:15 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	sprites_data(t_gsprite *sprite, char **map)
{
	sprite->all_num = sprites_number(map);
	sprite->all = (t_sprite *)malloc(sizeof(t_sprite) * sprite->all_num);
	sprite->visible = (t_sprite *)malloc(sizeof(t_sprite) * sprite->all_num);
	sprites_coordinates(sprite->all, map);
}

int	sprites_number(char **map)
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
			if (map[y][x] == 's')
				sprites_num++;
	}
	return (sprites_num);
}

void	sprites_coordinates(t_sprite *sprites, char **map)
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
			if (map[y][x] == 's')
			{
				sprites[i].x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				sprites[i].y = (y * TILE_SIZE) + (TILE_SIZE / 2);
				i++;
			}
		}
	}
}

void	sort_visible_sprites(t_data *data)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < data->sprite.visible_num - 1)
	{
		j = i + 1;
		while (j < data->sprite.visible_num)
		{
			if (data->sprite.visible[i].distance < \
				data->sprite.visible[j].distance)
			{
				tmp = data->sprite.visible[i];
				data->sprite.visible[i] = data->sprite.visible[j];
				data->sprite.visible[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
