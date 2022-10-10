/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:38:08 by aamajane          #+#    #+#             */
/*   Updated: 2022/09/17 18:18:05 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ray_facing_down(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int	ray_facing_up(double angle)
{
	return (!ray_facing_down(angle));
}

int	ray_facing_right(double angle)
{
	if (angle < M_PI / 2 || angle > 3 * M_PI / 2)
		return (1);
	return (0);
}

int	ray_facing_left(double angle)
{
	return (!ray_facing_right(angle));
}
