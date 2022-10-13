/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:29:52 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/13 16:00:32 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**read_file(char *arg)
{
	char	**file;
	int		fd;
	int		i;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		exit(puterror("Cub3D file not found"));
	file = (char **)malloc(sizeof(char *) * 1000);
	i = 0;
	file[i] = get_next_line(fd);
	if (!file[i])
		exit(puterror("Cub3D file unreadable"));
	while (file[i++])
		file[i] = get_next_line(fd);
	close(fd);
	return (file);
}

void	separate_file_elements(t_elm *elm, char ***tmp_elm, char **file)
{
	int	i;
	int	j;

	i = -1;
	*tmp_elm = (char **)malloc(sizeof(char *) * 7);
	j = 0;
	while (file[++i] && j < 6)
		if (ft_strncmp(file[i], "\n", ft_strlen(file[i])))
			(*tmp_elm)[j++] = ft_substr(file[i], 0, ft_strlen(file[i]) - 1);
	(*tmp_elm)[j] = NULL;
	if (ft_strncmp(file[i], "\n", ft_strlen(file[i])))
		i++;
	elm->map_width = map_width(file + i);
	elm->map_height = map_height(file + i--);
	elm->map = (char **)ft_calloc(elm->map_height + 1, sizeof(char *));
	j = 0;
	while (file[++i])
	{
		elm->map[j] = (char *)ft_calloc(elm->map_width + 1, sizeof(char));
		if (file[i][ft_strlen(file[i]) - 1] == '\n')
			ft_strlcpy(elm->map[j++], file[i], ft_strlen(file[i]));
		else
			ft_strlcpy(elm->map[j++], file[i], ft_strlen(file[i]) + 1);
	}
	elm->map[j] = NULL;
}

int	is_color(char *str, int **count)
{
	if (!ft_strncmp(str, "F ", 2))
	{
		(*count)[0]++;
		return (0);
	}
	if (!ft_strncmp(str, "C ", 2))
	{
		(*count)[1]++;
		return (1);
	}
	return (-1);
}

int	is_direction(char *str, int **count)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		(*count)[2]++;
		return (NORTH);
	}
	if (!ft_strncmp(str, "SO ", 3))
	{
		(*count)[3]++;
		return (SOUTH);
	}
	if (!ft_strncmp(str, "EA ", 3))
	{
		(*count)[4]++;
		return (EAST);
	}
	if (!ft_strncmp(str, "WE ", 3))
	{
		(*count)[5]++;
		return (WEST);
	}
	return (-1);
}

int	*copy_rgb_color(char **tab)
{
	int	*rgb;
	int	i;

	rgb = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (tab[++i])
	{
		rgb[i] = ft_atoi(tab[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			exit(puterror("Invalid color"));
	}
	return (rgb);
}
