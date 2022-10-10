/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical_intercept.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:14:05 by aamajane          #+#    #+#             */
/*   Updated: 2022/09/14 18:34:41 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	vertical_intercept(t_hit *vertical, t_data *data, double ray_angle)
{
	t_intercept	vert;

	vertical->wall_hit = 0;
	first_vert_intercept(&vert, data, ray_angle);
	xy_vertical_steps(&vert, ray_angle);
	if (ray_facing_left(ray_angle))
		vert.xintercept -= 1;
	while (is_inside_map(data, vert.xintercept, vert.yintercept))
	{
		if (map_has_wall_at(data, vert.xintercept, vert.yintercept))
		{
			if (ray_facing_left(ray_angle))
				vert.xintercept += 1;
			vertical->wall_hit_x = vert.xintercept;
			vertical->wall_hit_y = vert.yintercept;
			vertical->wall_hit = 1;
			break ;
		}
		vert.xintercept += vert.xstep;
		vert.yintercept += vert.ystep;
	}
}

void	first_vert_intercept(t_intercept *vert, t_data *data, double ray_angle)
{
	vert->xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray_facing_right(ray_angle))
		vert->xintercept += TILE_SIZE;
	vert->yintercept = \
		data->player.y + ((vert->xintercept - data->player.x) * tan(ray_angle));
}

void	xy_vertical_steps(t_intercept *vert, double ray_angle)
{
	vert->xstep = TILE_SIZE;
	if (ray_facing_left(ray_angle))
		vert->xstep *= -1;
	vert->ystep = TILE_SIZE * tan(ray_angle);
	if ((ray_facing_up(ray_angle) && vert->ystep > 0) || \
		(ray_facing_down(ray_angle) && vert->ystep < 0))
		vert->ystep *= -1;
}
