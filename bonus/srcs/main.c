/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:11:19 by aamajane          #+#    #+#             */
/*   Updated: 2022/09/25 17:05:07 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
*  Change user in order to play music
*/

void	ft_afplay(t_data *data)
{
	char *afplay[3];
	int pid;

	afplay[0] = "/usr/bin/afplay";
	if (data->music == SONG)
		afplay[1] = data->afplay[1];
	afplay[2] = 0;
	pid = fork();
	data->pid = pid;
	if (pid == 0)
		execve(afplay[0], afplay, 0);
	//free_double_pointer(data->afplay);
}

void	ft_afplay_run(t_data *data)
{
	char *afplay[3];
	int pid;

	afplay[0] = "/usr/bin/afplay";
	afplay[1] = "/Users/ablaamim/Desktop/42Cursus-Cub3D/.sound/run.mp3";
	afplay[2] = 0;
	pid = fork();
	data->pid = pid;
	if (pid == 0)
		execve(afplay[0], afplay, 0);
	//free_double_pointer(data->afplay);
}

void	init_extra(t_data *data)
{
	data->afplay = (char **)malloc(sizeof(char *) * 3);
	if (data == 0x0)
		write(2, "Error : System malloc() failed", sizeof("Error : System malloc() failed"));
	data->flag = 0x0;
	data->pid = 0x0;
	data->frames = 0x0;
	data->max_frames = 0x0;
	data->keys.a = false;
	data->keys.s = false;
	data->keys.d = false;
	data->keys.w = false;
	data->keys.left_arrow = false;
	data->keys.right_arrow = false;
	data->keys.up_arrow = false;
	data->keys.down_arrow = false;
	data->keys.shift = false;
	data->keys.c = false;
	data->keys.r = false;

}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit(puterror("Cub3D takes only one argument"));
	init_extra(&data);
	checker(&data.elm, av[1]);
	create_game(&data);
	free(&data.afplay);
	return (0);
}

int	puterror(char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	free_double_pointer(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
