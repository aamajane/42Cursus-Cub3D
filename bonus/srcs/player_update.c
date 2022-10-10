/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 21:00:29 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/10 22:59:12 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	player_update(t_data *data)
{
	if (data->player.mov_direction != 0)
		move_player(data);
	if (data->player.rot_direction != 0)
		rotate_player(data);
}

void	move_player(t_data *data)
{
	double	player_rotaion_angle;
	double	player_mov;
	double	x_to_check;
	double	y_to_check;

	player_rotaion_angle = data->player.rot_angle - data->player.side_angle;
	player_mov = (data->player.mov_speed + 10) * data->player.mov_direction;
	x_to_check = player_mov * cos(player_rotaion_angle) + data->player.x;
	y_to_check = player_mov * sin(player_rotaion_angle) + data->player.y;
	if (map_content(data, x_to_check, y_to_check, TILE_SIZE) != '0')
		return ;
	player_mov = data->player.mov_speed * data->player.mov_direction;
	data->player.x = player_mov * cos(player_rotaion_angle) + data->player.x;
	data->player.y = player_mov * sin(player_rotaion_angle) + data->player.y;
}

void	rotate_player(t_data *data)
{
	double	player_rot;

	player_rot = data->player.rot_speed * data->player.rot_direction;
	data->player.rot_angle += player_rot;
	normalize_angle(&data->player.rot_angle);
}
