/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:11:19 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 22:41:31 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		exit(puterror("Cub3D takes only one argument"));
	checker(&data.elm, av[1]);
	create_game(&data);
	return (0);
}

int	puterror(char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	free_double_pointer(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
