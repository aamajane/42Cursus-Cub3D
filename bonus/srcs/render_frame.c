/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:35:14 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 20:20:12 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	render_frame(t_data *data)
{
	player_update(data);
	raycasting(data);
	projection(data);
	render_3d_projection(data);
	if (data->door.render)
		render_door(data);
	render_enemy_projection(data);
	render_weapon(data);
	render_target(data);
	mlx_put_image_to_window(data->mlx, data->win, data->main_img.addr, 0, 0);
	render_minimap(data);
	menu(data);
	return (0);
}

void	render_3d_projection(t_data *data)
{
	int	x;
	int	light_num;

	x = -1;
	while (++x < NUM_RAYS)
	{
		if (data->rays[x].hit_content == door)
			render_projected_column(data, x, data->door.img);
		else if (data->rays[x].hit_content >= light_1 && \
				data->rays[x].hit_content <= light_4)
		{
			light_num = data->rays[x].hit_content - 100;
			render_projected_column(data, x, \
				data->lights[light_num].imgs[data->lights[light_num].index]);
		}
		else
			render_projected_column(data, x, \
								data->walls[data->rays[x].hit_content]);
		render_celing(data, x);
		render_floor(data, x);
	}
	light_timer(data);
}

void	render_projected_column(t_data *data, int x, t_img img)
{
	int	offset_index;
	int	offset_x;
	int	offset_y;
	int	index;
	int	y;

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
		offset_index = (offset_y * img.line_length) + offset_x;
		data->main_img.buffer[index] = \
							increase_color_intensity(data->rays[x].distance, \
													img.buffer[offset_index]);
		y++;
	}
}

void	render_celing(t_data *data, int x)
{
	double	intensity_factor;
	int		ceiling_color;
	int		index;
	int		y;

	intensity_factor = 256;
	ceiling_color = 0x003B3B3B;
	y = 0;
	while (y < data->column[x].top_y)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = \
				increase_color_intensity(intensity_factor++, ceiling_color);
		y++;
	}
}

void	render_floor(t_data *data, int x)
{
	double	intensity_factor;
	int		floor_color;
	int		index;
	int		y;

	intensity_factor = WIN_HEIGHT - data->column[x].bottom_y + 256;
	floor_color = 0x003B3B3B;
	y = data->column[x].bottom_y;
	while (y < WIN_HEIGHT)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = \
				increase_color_intensity(intensity_factor--, floor_color);
		y++;
	}
}
