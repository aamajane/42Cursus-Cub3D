/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:55:44 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/09 21:20:48 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	hooks_press_setter(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys.w = true;
	else if (keycode == A_KEY)
		data->keys.a = true;
	else if (keycode == S_KEY)
		data->keys.s = true;
	else if (keycode == D_KEY)
		data->keys.d = true;
	else if (keycode == LEFT_KEY)
		data->keys.left_arrow = true;
	else if (keycode == RIGHI_KEY)
		data->keys.right_arrow = true;
	else if (keycode == UP_KEY)
		data->keys.up_arrow = true;
	else if (keycode == DOWN_KEY)
		data->keys.down_arrow = true;
	else if (keycode == KEY_C)
		data->keys.c = true;
	else if (keycode == KEY_R)
		data->keys.r = true;
	else if (keycode == KEY_SHIFT)
		data->keys.shift = true;
	else if (keycode == ENTRE_KEY)
		data->keys.enter = true;
}

void	hooks_release_setter(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->keys.w = false;
	else if (keycode == A_KEY)
		data->keys.a = false;
	else if (keycode == S_KEY)
		data->keys.s = false;
	else if (keycode == D_KEY)
		data->keys.d = false;
	else if (keycode == LEFT_KEY)
		data->keys.left_arrow = false;
	else if (keycode == RIGHI_KEY)
		data->keys.right_arrow = false;
	else if (keycode == UP_KEY)
		data->keys.up_arrow = false;
	else if (keycode == DOWN_KEY)
		data->keys.down_arrow = false;
	else if (keycode == KEY_C)
		data->keys.c = false;
	else if (keycode == KEY_R)
		data->keys.r = false;
	else if (keycode == KEY_SHIFT)
		data->keys.shift = false;
	else if (keycode == ENTRE_KEY)
		data->keys.enter = false;
}

int	key_press(int keycode, t_data *data)
{
	hooks_press_setter(keycode, data);
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
	else if (keycode == ENTRE_KEY)
		data->door.entre = 1;
	else if (keycode == KEY_R)
	{
		data->music = SONG;
		data->afplay[1] = MUSIC;
		if (data->pid == 0x0)
			ft_afplay(data);
	}
	else if (keycode == KEY_C)
		kill(data->pid, SIGKILL);
	else if (keycode == KEY_SHIFT)
		data->player.mov_speed = SHIFT_MODE;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	hooks_release_setter(keycode, data);
	if (keycode == W_KEY || keycode == A_KEY || \
		keycode == S_KEY || keycode == D_KEY || \
		keycode == UP_KEY || keycode == DOWN_KEY)
		data->player.mov_direction = 0;
	else if (keycode == RIGHI_KEY || keycode == LEFT_KEY)
		data->player.rot_direction = 0;
	else if (keycode == KEY_C)
	{
		data->pid = 0x0;
	}
	else if (keycode == ENTRE_KEY)
		data->door.entre = 0;
	else if (keycode == KEY_SHIFT)
		data->player.mov_speed = NORMAL_MODE;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	data->player.rot_direction = 0;
	if (x >= 0 && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		data->player.rot_direction = (x - (WIN_WIDTH / 2)) / 1000.0;
	return (0);
}

int	close_win(t_data *data)
{
	if (data->pid != 0x0)
		kill(data->pid, SIGKILL);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
