/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 00:22:25 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/07 23:46:50 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	render_minimap(t_data *data)
{
	t_mini	mini;

	draw_minimap(data, &mini);
	draw_rect(data, mini.player_x - (RECT_SIZE / 2), \
					mini.player_y - (RECT_SIZE / 2), 0x00BF0000);
	draw_minimap_border(data);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.addr, 10, 10);
	mlx_put_image_to_window(data->mlx, data->win, data->letters[letter_n].addr, \
							MINIMAP_WIDTH / 2, 1);
	mlx_put_image_to_window(data->mlx, data->win, data->letters[letter_s].addr, \
							MINIMAP_WIDTH / 2, MINIMAP_HEIGHT - 5);
	mlx_put_image_to_window(data->mlx, data->win, data->letters[letter_e].addr, \
							MINIMAP_WIDTH - 5, MINIMAP_HEIGHT / 2);
	mlx_put_image_to_window(data->mlx, data->win, data->letters[letter_w].addr, \
							1, MINIMAP_HEIGHT / 2);
}

void	draw_minimap(t_data *data, t_mini *mini)
{
	get_minimap_y(data, mini);
	mini->img_y = -1;
	while (++mini->img_y < MINIMAP_HEIGHT && \
			++mini->map_y < data->elm.map_height * MINI_SIZE)
	{
		get_minimap_x(data, mini);
		mini->img_x = -1;
		while (++mini->img_x < MINIMAP_WIDTH && \
				++mini->map_x < data->elm.map_width * MINI_SIZE)
		{
			mini->index = mini->img_y * data->minimap.line_length + mini->img_x;
			mini->c = map_content(data, mini->map_x, mini->map_y, MINI_SIZE);
			data->minimap.buffer[mini->index] = 0x00000000;
			if (mini->c && mini->c != '0' && mini->c != ' ' && mini->c != 's')
				data->minimap.buffer[mini->index] = 0x00525252;
			if (mini->c == 'd')
				data->minimap.buffer[mini->index] = 0x00696969;
			if (mini->map_x == (int)(data->player.x / TILE_SIZE * MINI_SIZE) && \
				mini->map_y == (int)(data->player.y / TILE_SIZE * MINI_SIZE))
			{
				mini->player_x = mini->img_x;
				mini->player_y = mini->img_y;
			}
		}
	}
}

void	get_minimap_y(t_data *data, t_mini *mini)
{
	mini->map_y = (data->player.y / TILE_SIZE * MINI_SIZE) - \
					(MINIMAP_HEIGHT / 2);
	if (mini->map_y < 0)
		mini->map_y = 0;
	if (mini->map_y + MINIMAP_HEIGHT > data->elm.map_height * MINI_SIZE)
		mini->map_y = (data->elm.map_height * MINI_SIZE) - MINIMAP_HEIGHT;
	mini->map_y--;
}

void	get_minimap_x(t_data *data, t_mini *mini)
{
	mini->map_x = (data->player.x / TILE_SIZE * MINI_SIZE) - \
					(MINIMAP_WIDTH / 2);
	if (mini->map_x < 0)
		mini->map_x = 0;
	if (mini->map_x + MINIMAP_WIDTH > data->elm.map_width * MINI_SIZE)
		mini->map_x = (data->elm.map_width * MINI_SIZE) - MINIMAP_WIDTH;
	mini->map_x--;
}

void	draw_minimap_border(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = -1;
		while (++x * RECT_SIZE < MINIMAP_WIDTH)
			draw_rect(data, x * RECT_SIZE, y, 0x00FFFFFF);
		y += MINIMAP_HEIGHT - RECT_SIZE;
	}
	x = 0;
	while (x < MINIMAP_WIDTH)
	{
		y = -1;
		while (++y * RECT_SIZE < MINIMAP_HEIGHT)
			draw_rect(data, x, y * RECT_SIZE, 0x00FFFFFF);
		x += MINIMAP_WIDTH - RECT_SIZE;
	}
}
