/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:28:53 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 17:22:57 by aamajane         ###   ########.fr       */
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
	t_r	r;

	r.txt_x = -1;
	r.win_x = data->weapon.x;
	while (++r.txt_x < data->weapon.width)
	{
		r.txt_y = -1;
		r.win_y = data->weapon.y;
		while (++r.txt_y < data->weapon.height)
		{
			r.win_index = (r.win_y * data->main_img.line_length) + r.win_x;
			r.txt_index = (r.txt_y * img.line_length) + r.txt_x;
			if (img.buffer[r.txt_index] != img.buffer[0])
				data->main_img.buffer[r.win_index] = img.buffer[r.txt_index];
			r.win_y++;
		}
		r.win_x++;
	}
}

void	weapon_shooting_timer(t_data *data)
{
	if (data->weapon.shooting_timer > 4)
	{
		data->weapon.shooting_index++;
		if (data->weapon.shooting_index == NUM_SHOOTING)
		{
			data->weapon.shooting_index = 0;
			data->weapon.render_shooting = 0;
			data->weapon.bullets--;
			kill(data->pid_gun, SIGKILL);
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

void	render_target(t_data *data)
{
	t_img	img;
	t_r		r;

	img = data->target[0];
	if (data->weapon.target)
		img = data->target[1];
	r.txt_x = -1;
	r.win_x = (WIN_WIDTH / 2) - (TILE_SIZE / 2);
	while (++r.txt_x < TILE_SIZE)
	{
		r.txt_y = -1;
		r.win_y = (WIN_HEIGHT / 2) - (TILE_SIZE / 2);
		while (++r.txt_y < TILE_SIZE)
		{
			r.win_index = (r.win_y * data->main_img.line_length) + r.win_x;
			r.txt_index = (r.txt_y * img.line_length) + r.txt_x;
			if (img.buffer[r.txt_index] != img.buffer[0])
				data->main_img.buffer[r.win_index] = img.buffer[r.txt_index];
			r.win_y++;
		}
		r.win_x++;
	}
}
