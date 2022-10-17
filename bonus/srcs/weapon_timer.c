/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_timer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:00:15 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/17 23:00:29 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
			ft_afplay(BULLET, &data->pid_bullet);
			if (data->pid_gunshot)
				kill(data->pid_gunshot, SIGKILL);
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
			if (data->pid_reload)
				kill(data->pid_reload, SIGKILL);
		}
		data->weapon.reloading_timer = 0;
	}
	data->weapon.reloading_timer++;
}

void	bullet_timer(t_data *data)
{
	if (data->weapon.bullet_timer > 8)
	{
		data->weapon.render_reloading = 0;
		data->weapon.reloading_timer = 0;
		if (data->pid_reload)
			kill(data->pid_bullet, SIGKILL);
	}
	data->weapon.reloading_timer++;
}
