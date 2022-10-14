/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:01:25 by ablaamim          #+#    #+#             */
/*   Updated: 2022/10/14 20:24:45 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
*  Change user in order to play music
*/

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
