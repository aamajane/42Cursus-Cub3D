/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:43:37 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 23:12:01 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	enemy_data(t_gsprite *gsprite, char **map)
{
	gsprite->all_num = sprites_number(map, 'e');
	gsprite->all = (t_sprite *)malloc(sizeof(t_sprite) * gsprite->all_num);
	gsprite->visible = (t_sprite *)malloc(sizeof(t_sprite) * gsprite->all_num);
	sprites_coordinates(gsprite->all, map, 'e');
}

void	render_enemy_projection(t_data *data)
{
	int	i;

	data->enemy.gsprite.visible_num = 0;
	find_visible_sprites(data, &data->enemy.gsprite);
	if (data->enemy.gsprite.visible_num)
	{
		sort_visible_sprites(&data->enemy.gsprite);
		i = -1;
		while (++i < data->enemy.gsprite.visible_num)
			sprite_projection(data, &data->enemy.gsprite.visible[i]);
		i = -1;
		while (++i < data->enemy.gsprite.visible_num)
			sprite_rendering(data, &data->enemy.gsprite.visible[i], \
							data->enemy.img);
	}
}
