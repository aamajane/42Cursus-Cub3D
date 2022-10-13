/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:57:39 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 22:12:09 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_weapon_images(t_data *data)
{
	int	width;
	int	height;
	int	i;

	width = data->weapon.width;
	height = data->weapon.height;
	data->weapon.holding.addr = mlx_xpm_file_to_image(data->mlx, \
								data->weapon.holding.path, &width, &height);
	data->weapon.holding.buffer = (int *)mlx_get_data_addr(\
									data->weapon.holding.addr, \
									&data->weapon.holding.bits_per_pixel, \
									&data->weapon.holding.line_length, \
									&data->weapon.holding.endian);
	data->weapon.holding.line_length /= 4;
	i = -1;
	init_weapon_images_extra(data, width, height, i);
}

void	init_weapon_images_extra(t_data *data, int width, int height, int i)
{
	while (++i < NUM_SHOOTING)
	{
		data->weapon.shooting[i].addr = mlx_xpm_file_to_image(data->mlx, \
								data->weapon.shooting[i].path, &width, &height);
		data->weapon.shooting[i].buffer = (int *)mlx_get_data_addr(\
									data->weapon.shooting[i].addr, \
									&data->weapon.shooting[i].bits_per_pixel, \
									&data->weapon.shooting[i].line_length, \
									&data->weapon.shooting[i].endian);
		data->weapon.shooting[i].line_length /= 4;
	}
	i = -1;
	while (++i < NUM_RELOADING)
	{
		data->weapon.reloading[i].addr = mlx_xpm_file_to_image(data->mlx, \
							data->weapon.reloading[i].path, &width, &height);
		data->weapon.reloading[i].buffer = (int *)mlx_get_data_addr(\
									data->weapon.reloading[i].addr, \
									&data->weapon.reloading[i].bits_per_pixel, \
									&data->weapon.reloading[i].line_length, \
									&data->weapon.reloading[i].endian);
		data->weapon.reloading[i].line_length /= 4;
	}
}

void	init_enemy_images(t_data *data, int size)
{
	data->enemy.img.addr = mlx_xpm_file_to_image(data->mlx, \
								data->enemy.img.path, &size, &size);
	data->enemy.img.buffer = (int *)mlx_get_data_addr(\
									data->enemy.img.addr, \
									&data->enemy.img.bits_per_pixel, \
									&data->enemy.img.line_length, \
									&data->enemy.img.endian);
	data->enemy.img.line_length /= 4;
}
