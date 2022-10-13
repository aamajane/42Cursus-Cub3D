/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:28:53 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 15:24:10 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_weapon(t_data *data)
{
	if (!data->weapon.bullets)
	{
		data->weapon.render_reloading = 1;
		data->weapon.render_shooting = 0;
	}
	if (!data->weapon.render_shooting && !data->weapon.render_reloading)
		render_weapon_frames(data, data->weapon.holding);
	if (data->weapon.render_shooting && !data->weapon.render_reloading)
	{
		render_weapon_frames(data, \
						data->weapon.shooting[data->weapon.shooting_index]);
		weapon_shooting_timer(data);
	}
	if (data->weapon.render_reloading && !data->weapon.render_shooting)
	{
		render_weapon_frames(data, \
						data->weapon.reloading[data->weapon.reloading_index]);
		weapon_reloading_timer(data);
	}
}

void	render_weapon_frames(t_data *data, t_img img)
{
	t_rwf	rwf;

	rwf.wpn_x = -1;
	rwf.x = data->weapon.x;
	while (++rwf.wpn_x < data->weapon.width)
	{
		rwf.wpn_y = -1;
		rwf.y = data->weapon.y;
		while (++rwf.wpn_y < data->weapon.height)
		{
			rwf.index = (rwf.y * data->main_img.line_length) + rwf.x;
			rwf.wpn_index = (rwf.wpn_y * img.line_length) + rwf.wpn_x;
			if (img.buffer[rwf.wpn_index] != img.buffer[0])
				data->main_img.buffer[rwf.index] = img.buffer[rwf.wpn_index];
			rwf.y++;
		}
		rwf.x++;
	}
}

void	weapon_shooting_timer(t_data *data)
{
	if (data->weapon.shooting_timer > 2)
	{
		data->weapon.shooting_index++;
		if (data->weapon.shooting_index == NUM_SHOOTING)
		{
			data->weapon.shooting_index = 0;
			data->weapon.render_shooting = 0;
			data->weapon.bullets--;
		}
		data->weapon.shooting_timer = 0;
	}
	data->weapon.shooting_timer++;
}

void	weapon_reloading_timer(t_data *data)
{
	if (data->weapon.reloading_timer > 4)
	{
		data->weapon.reloading_index++;
		if (data->weapon.reloading_index == NUM_RELOADING)
		{
			data->weapon.reloading_index = 0;
			data->weapon.render_reloading = 0;
			data->weapon.bullets = NUM_BULLETS;
		}
		data->weapon.reloading_timer = 0;
	}
	data->weapon.reloading_timer++;
}
