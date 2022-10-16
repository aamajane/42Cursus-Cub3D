/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:01:25 by ablaamim          #+#    #+#             */
/*   Updated: 2022/10/16 21:21:23 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_afplay(char *sound, int *pid)
{
	char	*afplay[3];

	afplay[0] = "/usr/bin/afplay";
	afplay[1] = sound;
	afplay[2] = NULL;
	*pid = fork();
	if (*pid == -1)
		exit(puterror("Failed to fork process"));
	if (*pid == 0)
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
	mlx_string_put(data->mlx, data->win, x_pos, y_pos, color, \
					"Move : [W] [A] [S] [D]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Turn : [<-] [->]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Run  : [SHIFT]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Shoot: [X]");
	mlx_string_put(data->mlx, data->win, x_pos, y_pos += 20, color, \
					"Quit : [ESC]");
}
