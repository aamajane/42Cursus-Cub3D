/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:43:24 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/10 22:15:18 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_images(t_data *data, int size)
{
	data->sprite.img.addr = mlx_xpm_file_to_image(data->mlx, \
								data->sprite.img.path, &size, &size);
	data->sprite.img.buffer = (int *)mlx_get_data_addr(\
									data->sprite.img.addr, \
									&data->sprite.img.bits_per_pixel, \
									&data->sprite.img.line_length, \
									&data->sprite.img.endian);
	data->sprite.img.line_length /= 4;
	init_walls_images(data, size);
	init_lights_images(data, size);
	init_door_images(data, size);
	init_letters_images(data, size);
}

void	init_walls_images(t_data *data, int size)
{
	int	i;

	i = -1;
	while (++i < NUM_WALLS)
	{
		data->walls[i].addr = mlx_xpm_file_to_image(data->mlx, \
									data->walls[i].path, &size, &size);
		data->walls[i].buffer = (int *)mlx_get_data_addr(\
									data->walls[i].addr, \
									&data->walls[i].bits_per_pixel, \
									&data->walls[i].line_length, \
									&data->walls[i].endian);
		data->walls[i].line_length /= 4;
	}
}

void	init_lights_images(t_data *data, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < NUM_LIGHTS)
	{
		j = -1;
		while (++j < NUM_LIGHTNING)
		{
			data->lights[i].imgs[j].addr = mlx_xpm_file_to_image(data->mlx, \
								data->lights[i].imgs[j].path, &size, &size);
			data->lights[i].imgs[j].buffer = (int *)mlx_get_data_addr(\
								data->lights[i].imgs[j].addr, \
								&data->lights[i].imgs[j].bits_per_pixel, \
								&data->lights[i].imgs[j].line_length, \
								&data->lights[i].imgs[j].endian);
			data->lights[i].imgs[j].line_length /= 4;
		}
	}	
}

void	init_door_images(t_data *data, int size)
{
	int	i;

	data->door.img.addr = mlx_xpm_file_to_image(data->mlx, \
										data->door.img.path, &size, &size);
	data->door.img.buffer = (int *)mlx_get_data_addr(\
										data->door.img.addr, \
										&data->door.img.bits_per_pixel, \
										&data->door.img.line_length, \
										&data->door.img.endian);
	data->door.img.line_length /= 4;
	i = -1;
	while (++i < NUM_OP_DOORS)
	{
		data->door.op_imgs[i].addr = mlx_xpm_file_to_image(data->mlx, \
									data->door.op_imgs[i].path, &size, &size);
		data->door.op_imgs[i].buffer = (int *)mlx_get_data_addr(\
										data->door.op_imgs[i].addr, \
										&data->door.op_imgs[i].bits_per_pixel, \
										&data->door.op_imgs[i].line_length, \
										&data->door.op_imgs[i].endian);
		data->door.op_imgs[i].line_length /= 4;
	}
}

void	init_letters_images(t_data *data, int size)
{
	int	i;

	i = -1;
	while (++i < NUM_LETTERS)
	{
		data->letters[i].addr = mlx_xpm_file_to_image(data->mlx, \
										data->letters[i].path, &size, &size);
		data->letters[i].buffer = (int *)mlx_get_data_addr(\
										data->letters[i].addr, \
										&data->letters[i].bits_per_pixel, \
										&data->letters[i].line_length, \
										&data->letters[i].endian);
		data->letters[i].line_length /= 4;
	}
}
