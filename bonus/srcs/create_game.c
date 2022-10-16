/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:17:39 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 22:07:37 by aamajane         ###   ########.fr       */
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
	ft_afplay(MUSIC, &data->pid_music);
	create_images(data);
	images_path(data);
	init_all_images(data, TILE_SIZE);
	init_variables(data);
	player_data(&data->player, data->elm.map);
	enemy_data(&data->enemy.gsprite, data->elm.map);
	random_wall(&data->elm.map);
	mlx_hook(data->win, 2, 0, key_press, data);
	mlx_hook(data->win, 3, 0, key_release, data);
	mlx_hook(data->win, 6, 0, mouse_move, data);
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
	data->minimap.addr = mlx_new_image(data->mlx, \
											MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!data->minimap.addr)
		exit(puterror("Failed to create image"));
	data->minimap.buffer = (int *)mlx_get_data_addr(data->minimap.addr, \
											&data->minimap.bits_per_pixel, \
											&data->minimap.line_length, \
											&data->minimap.endian);
	data->minimap.line_length /= 4;
}

void	init_variables(t_data *data)
{
	data->door.is_open = 0;
	data->door.render = 0;
	data->door.index = 0;
	data->door.timer = 0;
	data->weapon.width = 800;
	data->weapon.height = 615;
	data->weapon.x = WIN_WIDTH - data->weapon.width;
	data->weapon.y = WIN_HEIGHT - data->weapon.height;
	data->weapon.bullets = NUM_BULLETS;
	data->weapon.render_shooting = 0;
	data->weapon.render_reloading = 0;
	data->weapon.shooting_index = 0;
	data->weapon.reloading_index = 0;
	data->weapon.shooting_timer = 0;
	data->weapon.reloading_timer = 0;
	data->weapon.target = 0;
	data->enemy.dying_index = 0;
	data->enemy.dying_timer = 0;
	data->enemy.dead_num = -1;
}

void	random_wall(char ***map)
{
	int	i;
	int	j;

	i = -1;
	while ((*map)[++i])
	{
		j = -1;
		while ((*map)[i][++j])
			if ((*map)[i][j] == '1')
				(*map)[i][j] = (rand() % (MAX_WALL_NUM + 1 - MIN_WALL_NUM) + \
								MIN_WALL_NUM) + '0';
	}	
}
