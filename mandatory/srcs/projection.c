/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:04:20 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/07 23:37:14 by aamajane         ###   ########.fr       */
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
		projection_facing_side(data, i);
	}
}

void	projection_facing_side(t_data *data, int i)
{
	if (ray_facing_up(data->rays[i].angle) && !data->rays[i].vertical_hit)
		data->column[i].facing_side = NORTH;
	if (ray_facing_down(data->rays[i].angle) && !data->rays[i].vertical_hit)
		data->column[i].facing_side = SOUTH;
	if (ray_facing_right(data->rays[i].angle) && data->rays[i].vertical_hit)
		data->column[i].facing_side = EAST;
	if (ray_facing_left(data->rays[i].angle) && data->rays[i].vertical_hit)
		data->column[i].facing_side = WEST;
}
