/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:33:58 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/10 23:05:15 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_door_near_player(t_data *data)
{
	double	ray_angle;
	t_hit	horizontal;
	t_hit	vertical;
	int		i;

	i = -1;
	while (++i < NUM_RAYS)
	{
		ray_angle = data->player.rot_angle + \
					(atan((i - (NUM_RAYS / 2)) / data->dist_proj_plane));
		normalize_angle(&ray_angle);
		data->rays[i].angle = ray_angle;
		door_horz_intercept(&horizontal, data, ray_angle);
		door_vert_intercept(&vertical, data, ray_angle);
		if (data->door.is_open)
			break ;
	}
	if (data->door.is_open && !door_distance(data, ray_angle, \
								data->door.xintercept, data->door.yintercept))
	{
		data->door.is_open = 0;
		data->door.render = 2;
		if (data->door.index == NUM_OP_DOORS)
			data->door.index--;
	}
}

void	door_horz_intercept(t_hit *horizontal, t_data *data, double ray_angle)
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
		if (horz.c == 'd' && data->door.entre && \
			door_distance(data, ray_angle, horz.xintercept, horz.yintercept))
		{
			data->door.xintercept = horz.xintercept;
			data->door.yintercept = horz.yintercept;
			data->door.vertical_hit = 0;
			data->door.is_open = 1;
			data->door.render = 1;
			data->elm.map[(int)floor(data->door.yintercept / TILE_SIZE)] \
						[(int)floor(data->door.xintercept / TILE_SIZE)] = '0';
			break ;
		}
		horz.xintercept += horz.xstep;
		horz.yintercept += horz.ystep;
	}
}

void	door_vert_intercept(t_hit *vertical, t_data *data, double ray_angle)
{
	t_intercept	vert;

	vertical->wall_hit = 0;
	first_vert_intercept(&vert, data, ray_angle);
	xy_vertical_steps(&vert, ray_angle);
	if (ray_facing_left(ray_angle))
		vert.xintercept -= 1;
	while (is_inside_map(data, vert.xintercept, vert.yintercept))
	{
		vert.c = map_content(data, vert.xintercept, vert.yintercept, TILE_SIZE);
		if (vert.c == 'd' && data->door.entre && \
			door_distance(data, ray_angle, vert.xintercept, vert.yintercept))
		{
			data->door.xintercept = vert.xintercept;
			data->door.yintercept = vert.yintercept;
			data->door.vertical_hit = 1;
			data->door.is_open = 1;
			data->door.render = 1;
			data->elm.map[(int)floor(data->door.yintercept / TILE_SIZE)] \
						[(int)floor(data->door.xintercept / TILE_SIZE)] = '0';
			break ;
		}
		vert.xintercept += vert.xstep;
		vert.yintercept += vert.ystep;
	}
}

int	door_distance(t_data *data, double ray_angle, double x, double y)
{
	double	distance;

	distance = cos(ray_angle - data->player.rot_angle) * \
				distance_between_points(data->player.x, data->player.y, x, y);
	if (distance <= 1.5 * TILE_SIZE)
		return (1);
	return (0);
}
