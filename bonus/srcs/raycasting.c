/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:57:39 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/09 22:22:55 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	raycasting(t_data *data)
{
	double	ray_angle;
	t_hit	horizontal;
	t_hit	vertical;
	int		i;

	data->dist_proj_plane = (WIN_WIDTH / 2) / tan(data->player.fov_angle / 2);
	check_door_near_player(data);
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray_angle = data->player.rot_angle + \
					(atan((i - (NUM_RAYS / 2)) / data->dist_proj_plane));
		normalize_angle(&ray_angle);
		data->rays[i].angle = ray_angle;
		horizontal_intercept(&horizontal, data, ray_angle);
		vertical_intercept(&vertical, data, ray_angle);
		calculate_distances(&horizontal, &vertical, \
							data->player.x, data->player.y);
		get_shortest_distance(&data->rays[i], &horizontal, &vertical);
	}
}

void	calculate_distances(t_hit *horizontal, t_hit *vertical, int px, int py)
{
	if (horizontal->wall_hit)
		horizontal->hit_distance = distance_between_points(px, py, \
								horizontal->wall_hit_x, horizontal->wall_hit_y);
	else
		horizontal->hit_distance = DBL_MAX;
	if (vertical->wall_hit)
		vertical->hit_distance = distance_between_points(px, py, \
								vertical->wall_hit_x, vertical->wall_hit_y);
	else
		vertical->hit_distance = DBL_MAX;
}

void	get_shortest_distance(t_ray *ray, t_hit *horizontal, t_hit *vertical)
{
	if (vertical->hit_distance < horizontal->hit_distance)
	{
		ray->distance = vertical->hit_distance;
		ray->wall_hit_x = vertical->wall_hit_x;
		ray->wall_hit_y = vertical->wall_hit_y;
		ray->hit_content = vertical->hit_content;
		ray->vertical_hit = 1;
	}
	else
	{
		ray->distance = horizontal->hit_distance;
		ray->wall_hit_x = horizontal->wall_hit_x;
		ray->wall_hit_y = horizontal->wall_hit_y;
		ray->hit_content = horizontal->hit_content;
		ray->vertical_hit = 0;
	}
	if (ray->distance == 0)
		ray->distance = 1;
}
