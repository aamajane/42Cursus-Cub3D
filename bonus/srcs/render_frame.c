/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:35:14 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/10 23:12:38 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static size_t	ft_get_digit(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n /= 10 ;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*nstr;
	size_t		dgt;
	long int	nb;

	nb = n;
	dgt = ft_get_digit(n);
	if (n < 0)
	{
		nb *= -1;
		dgt++;
	}
	nstr = (char *)malloc(sizeof(char) * (dgt + 1));
	if (!nstr)
		return (NULL);
	nstr[dgt] = '\0';
	while (dgt--)
	{
		nstr[dgt] = nb % 10 + '0';
		nb /= 10 ;
	}
	if (n < 0)
		nstr [0] = '-';
	return (nstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		joined[i++] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		joined[i++] = s2[j];
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

void	menu(t_data *g)
{
	void	*mlx;
	int		add;
	void	*win;
	//char	*frame;

	add = 0x0;
	mlx = g->mlx;
	win = g->win;
	//frame = (char *) malloc(sizeof(char) * (ft_strlen("FPS : ") + 3));
	//frame = ft_strjoin("FPS : ", ft_itoa(g->max_frames));
	mlx_string_put(mlx, win, SCREEN_POS + 50, add += 15, WHITE, "Controls :");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Move [W] [A] [S] [D]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Quit [ESC]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Look [<-] [->]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Run [SHIFT]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Shoot [x]");
	mlx_string_put(mlx, win, 135, add += 605, WHITE, "health");
	//mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, frame);
	//free(frame);
	//if (frame != NULL)
		//printf("NOT FREED\n");
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int index;

	(void) y;
	//while (y < WIN_HEIGHT)
	//{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = color;
	//	y++;
//	}
}


void	draw_square(t_data *g, int *coord, int sidelen, int color)
{
	int	x;
	int	y;

	y = coord[1];
	while (y < coord[1] + sidelen)
	{
		x = coord[0];
		while (x < coord[0] + sidelen)
		{
			my_mlx_pixel_put(g, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_square_middle_screen(t_data *g)
{
	int side_len;
	int coordinates[2];

	side_len = 8;
	coordinates[0] = WIN_WIDTH / 2 - side_len / 2;
	coordinates[1] = WIN_HEIGHT / 2 - side_len / 2;
	draw_square(g, coordinates, side_len, 0x00FF0000);
}

void	draw_rectangle(t_data *g, int *coord, int width, int height, int color)
{
	int	x;
	int	y;

	y = coord[1];
	while (y < coord[1] + height)
	{
		x = coord[0];
		while (x < coord[0] + width)
		{
			my_mlx_pixel_put(g, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_health_bar(t_data *g)
{
	int side_len;
	int coordinates[2];

	side_len = 10;
	coordinates[0] = 10;
	coordinates[1] = 700;
	draw_rectangle(g, coordinates, 320, 14, 0x0000FF00);
}

void health_bar(t_data *g)
{
	draw_health_bar(g);
}

int	render_frame(t_data *data)
{
	if (++data->frames >= 60)
	{
		data->max_frames = 60;
		data->frames = 0;	
	}
	player_update(data);
	raycasting(data);
	projection(data);
	render_3d_projection(data);
	render_sprites_projection(data);
	if (data->door.render)
		render_door(data);
	health_bar(data);
	draw_square_middle_screen(data);
	mlx_put_image_to_window(data->mlx, data->win, data->main_img.addr, 0, 0);
	render_minimap(data);
	menu(data);
	return (0);
}

void	render_3d_projection(t_data *data)
{
	int	x;
	int	light_num;

	x = -1;
	while (++x < NUM_RAYS)
	{
		if (data->rays[x].hit_content == door)
			render_projected_column(data, x, data->door.img);
		else if (data->rays[x].hit_content >= light_1 && \
				data->rays[x].hit_content <= light_4)
		{
			light_num = data->rays[x].hit_content - 100;
			render_projected_column(data, x, \
				data->lights[light_num].imgs[data->lights[light_num].index]);
		}
		else
			render_projected_column(data, x, \
								data->walls[data->rays[x].hit_content]);
		render_celing(data, x);
		render_floor(data, x);
	}
	light_timer(data);
}

void	render_projected_column(t_data *data, int x, t_img img)
{
	int	offset_index;
	int	offset_x;
	int	offset_y;
	int	index;
	int	y;

	if (data->rays[x].vertical_hit)
		offset_x = (int)data->rays[x].wall_hit_y % TILE_SIZE;
	else
		offset_x = (int)data->rays[x].wall_hit_x % TILE_SIZE;
	y = data->column[x].top_y;
	while (y < data->column[x].bottom_y)
	{
		offset_y = (y + data->column[x].dist_from_top) * \
					((double)TILE_SIZE / data->column[x].height);
		index = (y * data->main_img.line_length) + x;
		offset_index = (offset_y * img.line_length) + offset_x;
		data->main_img.buffer[index] = \
							increase_color_intensity(data->rays[x].distance, \
													img.buffer[offset_index]);
		y++;
	}
}

void	render_celing(t_data *data, int x)
{
	double	intensity_factor;
	int		ceiling_color;
	int		index;
	int		y;

	intensity_factor = 256;
	ceiling_color = 0x003B3B3B;
	y = 0;
	while (y < data->column[x].top_y)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = \
				increase_color_intensity(intensity_factor++, ceiling_color);
		y++;
	}
}

void	render_floor(t_data *data, int x)
{
	double	intensity_factor;
	int		floor_color;
	int		index;
	int		y;

	intensity_factor = WIN_HEIGHT - data->column[x].bottom_y + 256;
	floor_color = 0x003B3B3B;
	y = data->column[x].bottom_y;
	while (y < WIN_HEIGHT)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = \
				increase_color_intensity(intensity_factor--, floor_color);
		y++;
	}
}
