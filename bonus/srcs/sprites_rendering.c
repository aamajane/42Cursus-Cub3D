/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:43:37 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/11 20:47:37 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_sprites_projection(t_data *data)
{
	int	i;

	data->sprite.visible_num = 0;
	find_visible_sprites(data, &data->sprite.visible_num);
	if (data->sprite.visible_num)
	{
		sort_visible_sprites(data);
		i = -1;
		while (++i < data->sprite.visible_num)
			sprite_projection(data, &data->sprite.visible[i]);
		i = -1;
		while (++i < data->sprite.visible_num)
			sprite_rendering(data, &data->sprite.visible[i], data->sprite.img);
	}
}

void	find_visible_sprites(t_data *data, int *visible_num)
{
	double	anlge_sprite_player;
	int		i;

	i = -1;
	while (++i < data->sprite.all_num)
	{
		anlge_sprite_player = data->player.rot_angle - \
								atan2(data->sprite.all[i].y - data->player.y, \
										data->sprite.all[i].x - data->player.x);
		if (anlge_sprite_player > M_PI)
			anlge_sprite_player -= 2 * M_PI;
		if (anlge_sprite_player < -M_PI)
			anlge_sprite_player += 2 * M_PI;
		anlge_sprite_player = fabs(anlge_sprite_player);
		if (anlge_sprite_player < (data->player.fov_angle / 2) + EPSILON)
		{
			data->sprite.visible[*visible_num].x = data->sprite.all[i].x;
			data->sprite.visible[*visible_num].y = data->sprite.all[i].y;
			data->sprite.visible[*visible_num].angle = anlge_sprite_player;
			data->sprite.visible[*visible_num].distance = \
					distance_between_points(data->sprite.all[i].x, \
					data->sprite.all[i].y, data->player.x, data->player.y);
			(*visible_num)++;
		}
	}
}

void	sprite_projection(t_data *data, t_sprite *sprite)
{
	double	perp_distance;

	perp_distance = sprite->distance * cos(sprite->angle);
	sprite->size = (int)(TILE_SIZE / perp_distance * data->dist_proj_plane);
	sprite->top_y = (WIN_HEIGHT - sprite->size) / 2;
	if (sprite->top_y < 0)
		sprite->top_y = 0;
	sprite->bottom_y = (WIN_HEIGHT + sprite->size) / 2;
	if (sprite->bottom_y > WIN_HEIGHT)
		sprite->bottom_y = WIN_HEIGHT;
	sprite->dist_from_top = (sprite->size - WIN_HEIGHT) / 2;
}

void	sprite_rendering(t_data *data, t_sprite *sprite, t_img sprite_img)
{
	int	x;

	sprite->angle = atan2(sprite->y - data->player.y, \
					sprite->x - data->player.x) - data->player.rot_angle;
	sprite->screen_x = tan(sprite->angle) * data->dist_proj_plane;
	sprite->left_x = sprite->screen_x + WIN_WIDTH / 2 - sprite->size / 2;
	sprite->right_x = sprite->left_x + sprite->size;
	x = sprite->left_x;
	while (x < sprite->right_x && x < WIN_WIDTH)
	{
		if (x >= 0)
			sprite_drawing(data, sprite, sprite_img, x);
		x++;
	}
}

void	sprite_drawing(t_data *data, t_sprite *sprite, t_img sprite_img, int x)
{
	int	offset_index;
	int	offset_x;
	int	offset_y;
	int	index;
	int	y;

	offset_x = (x - sprite->left_x) * ((double)TILE_SIZE / sprite->size);
	y = sprite->top_y;
	while (y < sprite->bottom_y && y < WIN_HEIGHT)
	{
		offset_y = (y + sprite->dist_from_top) * \
					((double)TILE_SIZE / sprite->size);
		index = (y * data->main_img.line_length) + x;
		offset_index = (offset_y * sprite_img.line_length) + offset_x;
		if (sprite->distance < data->rays[x].distance && \
			sprite_img.buffer[offset_index] != sprite_img.buffer[0])
		{
			data->main_img.buffer[index] = \
					increase_color_intensity(sprite->distance, \
											sprite_img.buffer[offset_index]);
		}
		y++;
	}
}
