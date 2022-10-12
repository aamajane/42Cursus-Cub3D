/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:35:14 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/06 20:49:13 by aamajane         ###   ########.fr       */
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

	add = 0x0;
	mlx = g->mlx;
	win = g->win;
	char *frame = ft_strjoin("FPS : ", ft_itoa(g->max_frames));
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Controls :");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Move [W] [A] [S] [D]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Quit [ESC]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Look [<-] [->]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, frame);
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
	menu(data);
	return (0);
}

void	render_3d_projection(t_data *data)
{
	int	x;

	x = -1;
	while (++x < NUM_RAYS)
	{
		render_ceiling(data, x);
		render_wall(data, x);
		render_floor(data, x);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->main_img.addr, 0, 0);
}

void	render_ceiling(t_data *data, int x)
{
	int	y;
	int	index;

	y = 0;
	while (y < data->column[x].top_y)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = data->elm.ceiling_color;
		y++;
	}
}

void	render_wall(t_data *data, int x)
{
	int	y;
	int	index;
	int	offset_x;
	int	offset_y;
	int	offset_index;

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
		offset_index = offset_x + (offset_y * \
					data->imgs[data->column[x].facing_side].line_length);
		data->main_img.buffer[index] = \
			data->imgs[data->column[x].facing_side].buffer[offset_index];
		y++;
	}
}

void	render_floor(t_data *data, int x)
{
	int	y;
	int	index;

	y = data->column[x].bottom_y;
	while (y < WIN_HEIGHT)
	{
		index = (y * data->main_img.line_length) + x;
		data->main_img.buffer[index] = data->elm.floor_color;
		y++;
	}
}
