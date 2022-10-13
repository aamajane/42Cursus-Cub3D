/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:38:20 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 16:11:47 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

double	degree_to_radian(double angle)
{
	return (angle * (M_PI / 180));
}

void	normalize_angle(double *angle)
{
	*angle = remainder(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += (2 * M_PI);
}

int	create_trgb(int transparency, int red, int green, int blue)
{
	int	trgb;

	trgb = 0;
	trgb += transparency << 24;
	trgb += red << 16;
	trgb += green << 8;
	trgb += blue;
	return (trgb);
}

int	commas_number(char *str)
{
	int	commas_num;
	int	i;

	commas_num = 0;
	i = -1;
	while (str[++i])
		if (str[i] == ',')
			commas_num++;
	return (commas_num);
}
