/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal_intercept.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:13:33 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 22:55:14 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	horizontal_intercept(t_hit *horizontal, t_data *data, double ray_angle)
{
	t_intercept	horz;

	horizontal->wall_hit = 0;
	first_horz_intercept(&horz, data, ray_angle);
	xy_horizontal_steps(&horz, ray_angle);
	if (ray_facing_up(ray_angle))
		horz.yintercept -= 1;
	while (is_inside_map(data, horz.xintercept, horz.yintercept))
	{
		horz.c = map_content(data, horz.xintercept, horz.yintercept, TILE_SIZE);
		if (horz.c != '0' && horz.c != 'e')
		{
			if (ray_facing_up(ray_angle))
				horz.yintercept += 1;
			horizontal->wall_hit_x = horz.xintercept;
			horizontal->wall_hit_y = horz.yintercept;
			horizontal->hit_content = (int)horz.c;
			horizontal->wall_hit = 1;
			break ;
		}
		horz.xintercept += horz.xstep;
		horz.yintercept += horz.ystep;
	}
}

void	first_horz_intercept(t_intercept *horz, t_data *data, double ray_angle)
{
	horz->yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray_facing_down(ray_angle))
		horz->yintercept += TILE_SIZE;
	horz->xintercept = \
		data->player.x + ((horz->yintercept - data->player.y) / tan(ray_angle));
}

void	xy_horizontal_steps(t_intercept *horz, double ray_angle)
{
	horz->ystep = TILE_SIZE;
	if (ray_facing_up(ray_angle))
		horz->ystep *= -1;
	horz->xstep = TILE_SIZE / tan(ray_angle);
	if ((ray_facing_left(ray_angle) && horz->xstep > 0) || \
		(ray_facing_right(ray_angle) && horz->xstep < 0))
		horz->xstep *= -1;
}
