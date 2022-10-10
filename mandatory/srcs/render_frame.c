/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:35:14 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/06 20:49:13 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	render_frame(t_data *data)
{
	player_update(data);
	raycasting(data);
	projection(data);
	render_3d_projection(data);
	return (0);
}

void	render_3d_projection(t_data *data)
{
	int	x;

	x = -1;
	while (++x < NUM_RAYS)
	{
		render_ceiling(data, x);
		render_wall(data, x);
		render_floor(data, x);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->main_img.addr, 0, 0);
}

void	render_ceiling(t_data *data, int x)
{
	int	y;
	int	index;

	y = 0;
	while (y < data->column[x].top_y)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = data->elm.ceiling_color;
		y++;
	}
}

void	render_wall(t_data *data, int x)
{
	int	y;
	int	index;
	int	offset_x;
	int	offset_y;
	int	offset_index;

	if (data->rays[x].vertical_hit)
		offset_x = (int)data->rays[x].wall_hit_y % TILE_SIZE;
	else
		offset_x = (int)data->rays[x].wall_hit_x % TILE_SIZE;
	y = data->column[x].top_y;
	while (y < data->column[x].bottom_y)
	{
		offset_y = (y + data->column[x].dist_from_top) * \
					((double)TILE_SIZE / data->column[x].height);
		index = (y * data->main_img.line_length) + x;
		offset_index = offset_x + (offset_y * \
					data->imgs[data->column[x].facing_side].line_length);
		data->main_img.buffer[index] = \
			data->imgs[data->column[x].facing_side].buffer[offset_index];
		y++;
	}
}

void	render_floor(t_data *data, int x)
{
	int	y;
	int	index;

	y = data->column[x].bottom_y;
	while (y < WIN_HEIGHT)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = data->elm.floor_color;
		y++;
	}
}
