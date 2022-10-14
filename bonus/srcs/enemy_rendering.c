/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:43:37 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 16:04:47 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	enemy_data(t_gsprite *gsprite, char **map)
{
	int	i;

	gsprite->all_num = sprites_number(map, 'e');
	gsprite->all = (t_sprite *)malloc(sizeof(t_sprite) * gsprite->all_num);
	gsprite->visible = \
				(t_sprite **)malloc(sizeof(t_sprite *) * gsprite->all_num);
	i = -1;
	while (++i < gsprite->all_num)
		gsprite->visible[i] = (t_sprite *)malloc(sizeof(t_sprite));
	sprites_coordinates(gsprite->all, map, 'e');
	init_sprites_data(gsprite->all, gsprite->all_num);
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
			sprite_projection(data, data->enemy.gsprite.visible[i]);
		i = -1;
		while (++i < data->enemy.gsprite.visible_num)
			render_enemy(data, i);
	}
}

void	render_enemy(t_data *data, int i)
{
	if (data->enemy.gsprite.visible[i]->health > 0 && \
		!data->enemy.gsprite.visible[i]->is_dead)
	{
		sprite_rendering(data, data->enemy.gsprite.visible[i], \
						data->enemy.walking[data->enemy.walking_index]);
		enemy_walking_timer(data);
	}
	else
	{
		sprite_rendering(data, data->enemy.gsprite.visible[i], \
						data->enemy.dying[data->enemy.dying_index]);
		enemy_dying_timer(data, i);
	}
	if (data->enemy.gsprite.visible[i]->left_x < (WIN_WIDTH / 2) && \
		data->enemy.gsprite.visible[i]->right_x > (WIN_WIDTH / 2) && \
		data->enemy.gsprite.visible[i]->on_target)
	{
		if (data->weapon.render_shooting == 1)
		{
			data->enemy.gsprite.visible[i]->health = 0;
			data->enemy.gsprite.visible[i]->is_dead = 1;
		}
		data->weapon.target = 1;
	}
	else
		data->weapon.target = 0;
}
