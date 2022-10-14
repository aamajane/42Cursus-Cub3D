/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:43:24 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 03:16:55 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_all_images(t_data *data, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < NUM_LETTERS)
		init_image(data, &data->letters[i], size);
	i = -1;
	while (++i < NUM_WALLS)
		init_image(data, &data->walls[i], size);
	i = -1;
	while (++i < NUM_LIGHTS)
	{
		j = -1;
		while (++j < NUM_LIGHTNING)
			init_image(data, &data->lights[i].imgs[j], size);
	}
	init_image(data, &data->door.img, size);
	i = -1;
	while (++i < NUM_OP_DOORS)
		init_image(data, &data->door.op_imgs[i], size);
	i = -1;
	while (++i < NUM_TARGETS)
		init_image(data, &data->target[i], size);
	init_all_images_extra(data, size);
}

void	init_all_images_extra(t_data *data, int size)
{
	int	i;

	init_image(data, &data->weapon.holding, size);
	i = -1;
	while (++i < NUM_SHOOTING)
		init_image(data, &data->weapon.shooting[i], size);
	i = -1;
	while (++i < NUM_RELOADING)
		init_image(data, &data->weapon.reloading[i], size);
	i = -1;
	while (++i < NUM_E_WALKING)
		init_image(data, &data->enemy.walking[i], size);
	i = -1;
	while (++i < NUM_E_ATTACKS)
		init_image(data, &data->enemy.attacking[i], size);
	i = -1;
	while (++i < NUM_E_DYING)
		init_image(data, &data->enemy.dying[i], size);
}

void	init_image(t_data *data, t_img *img, int size)
{
	img->addr = mlx_xpm_file_to_image(data->mlx, img->path, &size, &size);
	img->buffer = (int *)mlx_get_data_addr(img->addr, &img->bits_per_pixel, \
									&img->line_length, &img->endian);
	img->line_length /= 4;
}
