/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:21:20 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 21:35:02 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	find_visible_sprites(t_data *data, t_gsprite *gsprite)
{
	double	anlge_sprite_player;
	int		i;

	i = -1;
	while (++i < gsprite->all_num)
	{
		anlge_sprite_player = data->player.rot_angle - \
								atan2(gsprite->all[i].y - data->player.y, \
										gsprite->all[i].x - data->player.x);
		if (anlge_sprite_player > M_PI)
			anlge_sprite_player -= 2 * M_PI;
		if (anlge_sprite_player < -M_PI)
			anlge_sprite_player += 2 * M_PI;
		anlge_sprite_player = fabs(anlge_sprite_player);
		if (anlge_sprite_player < (data->player.fov_angle / 2) + EPSILON)
		{
			gsprite->all[i].angle = anlge_sprite_player;
			gsprite->all[i].distance = \
					distance_between_points(gsprite->all[i].x, \
					gsprite->all[i].y, data->player.x, data->player.y);
			gsprite->visible[gsprite->visible_num] = &gsprite->all[i];
			(gsprite->visible_num)++;
		}
	}
}

void	sort_visible_sprites(t_gsprite *gsprite)
{
	t_sprite	*tmp;
	int			i;
	int			j;

	i = 0;
	while (i < gsprite->visible_num - 1)
	{
		j = i + 1;
		while (j < gsprite->visible_num)
		{
			if (gsprite->visible[i]->distance < \
				gsprite->visible[j]->distance)
			{
				tmp = gsprite->visible[i];
				gsprite->visible[i] = gsprite->visible[j];
				gsprite->visible[j] = tmp;
			}
			j++;
		}
		i++;
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
			sprite->on_target = 1;
			data->main_img.buffer[index] = \
					increase_color_intensity(sprite->distance, \
											sprite_img.buffer[offset_index]);
		}
		y++;
	}
}
