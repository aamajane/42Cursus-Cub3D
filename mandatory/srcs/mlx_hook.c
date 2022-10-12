/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:55:44 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/11 15:53:37 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		close_win(data);
	else if (keycode == W_KEY || keycode == A_KEY || keycode == UP_KEY)
	{
		data->player.mov_direction = 1;
		data->player.side_angle = 0;
		if (keycode == A_KEY)
			data->player.side_angle = M_PI / 2;
	}
	else if (keycode == S_KEY || keycode == D_KEY || keycode == DOWN_KEY)
	{
		data->player.mov_direction = -1;
		data->player.side_angle = 0;
		if (keycode == D_KEY)
			data->player.side_angle = M_PI / 2;
	}
	else if (keycode == RIGHI_KEY)
		data->player.rot_direction = 1;
	else if (keycode == LEFT_KEY)
		data->player.rot_direction = -1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY || keycode == A_KEY || \
		keycode == S_KEY || keycode == D_KEY || \
		keycode == UP_KEY || keycode == DOWN_KEY )
		data->player.mov_direction = 0;
	else if (keycode == RIGHI_KEY || keycode == LEFT_KEY)
		data->player.rot_direction = 0;
	return (0);
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
