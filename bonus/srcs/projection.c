/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:04:20 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 02:20:58 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	projection(t_data *data)
{
	double	perp_distance;
	int		i;

	i = -1;
	while (++i < NUM_RAYS)
	{
		perp_distance = data->rays[i].distance * \
							cos(data->rays[i].angle - data->player.rot_angle);
		data->column[i].height = \
					(int)(TILE_SIZE / perp_distance * data->dist_proj_plane);
		data->column[i].top_y = \
							(WIN_HEIGHT - data->column[i].height) / 2;
		if (data->column[i].top_y < 0)
			data->column[i].top_y = 0;
		data->column[i].bottom_y = \
							(WIN_HEIGHT + data->column[i].height) / 2;
		if (data->column[i].bottom_y > WIN_HEIGHT)
			data->column[i].bottom_y = WIN_HEIGHT;
		data->column[i].dist_from_top = \
							(data->column[i].height - WIN_HEIGHT) / 2;
		projection_content(data, i);
	}
}

void	projection_content(t_data *data, int i)
{
	if (data->rays[i].hit_content == 'd')
		data->rays[i].hit_content = door;
	else if (data->rays[i].hit_content == '1' + NUM_WALLS)
		data->rays[i].hit_content = light_1;
	else if (data->rays[i].hit_content == '1' + NUM_WALLS + 1)
		data->rays[i].hit_content = light_2;
	else if (data->rays[i].hit_content == '1' + NUM_WALLS + 2)
		data->rays[i].hit_content = light_3;
	else if (data->rays[i].hit_content == '1' + NUM_WALLS + 3)
		data->rays[i].hit_content = light_4;
	else if (is_wall(data->rays[i].hit_content))
		data->rays[i].hit_content = is_wall(data->rays[i].hit_content) - 1;
}

void	light_timer(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NUM_LIGHTS)
	{
		if (data->lights[i].timer > 30)
		{
			data->lights[i].index++;
			if (data->lights[i].index == NUM_LIGHTNING)
				data->lights[i].index = 0;
			data->lights[i].timer = 0;
		}
		data->lights[i].timer++;
	}
}
