/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:17:39 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 15:33:27 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	create_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		puterror("Failed to initialize mlx");
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		exit(puterror("Failed to create window"));
	create_images(data);
	init_images(data);
	player_data(&data->player, data->elm.map);
	mlx_hook(data->win, 2, 0, key_press, data);
	mlx_hook(data->win, 3, 0, key_release, data);
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}

void	create_images(t_data *data)
{
	data->main_img.addr = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->main_img.addr)
		exit(puterror("Failed to create image"));
	data->main_img.buffer = (int *)mlx_get_data_addr(data->main_img.addr, \
											&data->main_img.bits_per_pixel, \
											&data->main_img.line_length, \
											&data->main_img.endian);
	data->main_img.line_length /= 4;
}

void	init_images(t_data *data)
{
	int	size;
	int	i;

	size = TILE_SIZE;
	i = -1;
	while (++i < NUM_IMG)
	{
		data->imgs[i].addr = mlx_xpm_file_to_image(data->mlx, \
											data->elm.path[i], &size, &size);
		if (!data->imgs[i].addr)
			exit(puterror("Failed to load image"));
		data->imgs[i].buffer = (int *)mlx_get_data_addr(data->imgs[i].addr, \
											&data->imgs[i].bits_per_pixel, \
											&data->imgs[i].line_length, \
											&data->imgs[i].endian);
		data->imgs[i].line_length /= 4;
	}
}
