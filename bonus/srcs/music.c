/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:01:25 by ablaamim          #+#    #+#             */
/*   Updated: 2022/10/16 20:08:24 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_afplay(t_data *data)
{
	char	*afplay[3];
	int		pid;

	afplay[0] = "/usr/bin/afplay";
	if (data->music == SONG)
		afplay[1] = data->afplay[1];
	afplay[2] = 0;
	pid = fork();
	data->pid = pid;
	if (pid == 0)
		execve(afplay[0], afplay, 0);
}

void	ft_afplay_global(t_data *data)
{
	char	*afplay[3];
	int		pid;

	afplay[0] = "/usr/bin/afplay";
	afplay[1] = MUSIC;
	afplay[2] = 0;
	pid = fork();
	data->pid = pid;
	if (pid == 0)
		execve(afplay[0], afplay, 0);
}

void	ft_afplay_gun(t_data *data)
{
	char	*afplay[3];
	int		pid;

	afplay[0] = "/usr/bin/afplay";
	if (data->music == GUN_SHOT)
		afplay[1] = data->afplay[1];
	afplay[2] = 0;
	pid = fork();
	data->pid_gun = pid;
	if (pid == 0)
		execve(afplay[0], afplay, 0);
}

void	render_menu(t_data *data)
{
	int	x_pos;
	int	y_pos;
	int	color;

	x_pos = 1050;
	y_pos = 0;
	color = 0x00FFFFFF;
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Move : [W] [A] [S] [D]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Turn : [<-] [->]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Run  : [SHIFT]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Shoot: [X]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Quit : [ESC]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Music: [R] [C]");
}
