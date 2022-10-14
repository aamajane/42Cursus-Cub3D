/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:54:47 by ablaamim          #+#    #+#             */
/*   Updated: 2022/10/14 20:25:08 by ablaamim         ###   ########.fr       */
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
