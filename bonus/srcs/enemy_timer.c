/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:53:15 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 00:55:13 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	enemy_walking_timer(t_data *data)
{
	if (data->enemy.walking_timer > 4)
	{
		data->enemy.walking_index++;
		if (data->enemy.walking_index == NUM_E_WALKING)
			data->enemy.walking_index = 0;
		data->enemy.walking_timer = 0;
	}
	data->enemy.walking_timer++;
}

void	enemy_attacking_timer(t_data *data)
{
	if (data->enemy.attacking_timer > 4)
	{
		data->enemy.attacking_index++;
		if (data->enemy.attacking_index == NUM_E_ATTACKS)
			data->enemy.attacking_index = 0;
		data->enemy.attacking_timer = 0;
	}
	data->enemy.attacking_timer++;
}

void	enemy_dying_timer(t_data *data)
{
	if (data->enemy.dying_timer > 4)
	{
		data->enemy.dying_index++;
		if (data->enemy.dying_index == NUM_E_DYING)
			data->enemy.dying_index = 0;
		data->enemy.dying_timer = 0;
	}
	data->enemy.dying_timer++;
}