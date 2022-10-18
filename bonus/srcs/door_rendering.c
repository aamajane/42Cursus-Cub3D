/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:02:58 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/18 01:38:54 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_door(t_data *data)
{
	data->door.sprite.x = data->door.xintercept;
	if (!data->door.vertical_hit)
		data->door.sprite.x = (floor(data->door.xintercept / TILE_SIZE) \
							* TILE_SIZE) + (TILE_SIZE / 2);
	data->door.sprite.y = data->door.yintercept;
	if (data->door.vertical_hit)
		data->door.sprite.y = (floor(data->door.yintercept / TILE_SIZE) \
							* TILE_SIZE) + (TILE_SIZE / 2);
	data->door.sprite.angle = data->player.rot_angle - \
								atan2(data->door.sprite.y - data->player.y, \
										data->door.sprite.x - data->player.x);
	data->door.sprite.distance = \
			distance_between_points(data->door.sprite.x, data->door.sprite.y, \
											data->player.x, data->player.y);
	sprite_projection(data, &data->door.sprite);
	sprite_rendering(data, &data->door.sprite, \
					data->door.op_imgs[data->door.index]);
	if (data->door.render == 1)
		door_opening_timer(data);
	if (data->door.render == 2)
		door_closing_timer(data);
}

void	door_opening_timer(t_data *data)
{
	if (data->door.timer > 5)
	{
		data->door.index++;
		if (data->door.index == NUM_OP_DOORS)
		{
			data->door.index--;
			data->door.render = 0;
			if (data->pid.door)
				kill(data->pid.door, SIGKILL);
		}
		data->door.timer = 0;
	}
	data->door.timer++;
}

void	door_closing_timer(t_data *data)
{
	if (data->door.timer > 6)
	{
		data->door.index--;
		if (data->door.index == -1)
		{
			data->door.index++;
			data->door.render = 0;
			data->elm.map[(int)floor(data->door.yintercept / TILE_SIZE)] \
					[(int)floor(data->door.xintercept / TILE_SIZE)] = 'd';
			if (data->pid.door)
				kill(data->pid.door, SIGKILL);
		}
		data->door.timer = 0;
	}
	data->door.timer++;
}
