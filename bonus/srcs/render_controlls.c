/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_controlls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:15:33 by ablaamim          #+#    #+#             */
/*   Updated: 2022/10/14 20:24:02 by ablaamim         ###   ########.fr       */
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
	mlx_string_put(mlx, win, SCREEN_POS + 50, add += 15, WHITE, "Controls :");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, \
			"Move [W] [A] [S] [D]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Quit [ESC]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Look [<-] [->]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Run [SHIFT]");
	mlx_string_put(mlx, win, SCREEN_POS, add += 15, WHITE, "Shoot [x]");
}
