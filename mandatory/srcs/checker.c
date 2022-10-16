/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:42:50 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 16:13:37 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	checker(t_elm *elm, char *arg)
{
	char	**tmp_elm;
	char	**file;

	if (ft_strncmp(arg + ft_strlen(arg) - 4, ".cub", 4) || ft_strlen(arg) <= 4)
		exit(puterror("file extension must be .cub"));
	file = read_file(arg);
	separate_file_elements(elm, &tmp_elm, file);
	free_double_pointer(file);
	elm->path = (char **)malloc(sizeof(char *) * 4);
	elm->rgb = (int **)malloc(sizeof(int *) * 2);
	check_elements(elm, tmp_elm);
	free_double_pointer(tmp_elm);
	elm->floor_color = \
				create_trgb(0, elm->rgb[0][0], elm->rgb[0][1], elm->rgb[0][2]);
	elm->ceiling_color = \
				create_trgb(0, elm->rgb[1][0], elm->rgb[1][1], elm->rgb[1][2]);
}

void	check_elements(t_elm *elm, char **tmp_elm)
{
	int	*count;
	int	i;
	int	j;
	int	color;
	int	direction;

	count = (int *)calloc(6, sizeof(int));
	i = -1;
	while (tmp_elm[++i])
	{
		skip_spaces(tmp_elm[i], &j);
		color = is_color(tmp_elm[i] + j, &count);
		direction = is_direction(tmp_elm[i] + j, &count);
		if (color >= 0)
			elm->rgb[color] = check_color(tmp_elm[i] + j + 2);
		else if (direction >= 0)
			elm->path[direction] = check_path(tmp_elm[i] + j + 3);
		else
			exit(puterror("Invalid element"));
	}
	if (count[0] != 1 || count[1] != 1 || count[2] != 1 || \
		count[3] != 1 || count[4] != 1 || count[5] != 1)
		exit(puterror("Invalid element"));
	free(count);
	check_map(elm->map);
}

int	*check_color(char *str)
{
	char	**tab;
	int		*rgb;
	int		i;
	int		j;

	skip_spaces(str, &i);
	if (commas_number(str + i) != 2)
		exit(puterror("Invalid color format"));
	tab = ft_split(str + i, ',');
	i = -1;
	while (tab[++i])
	{
		j = 0;
		if (ft_strlen(tab[i]) > 3)
			exit(puterror("Invalid color"));
		while (tab[i][j])
			if (!ft_isdigit(tab[i][j++]))
				exit(puterror("Invalid color"));
	}
	if (i != 3)
		exit(puterror("Invalid color"));
	rgb = copy_rgb_color(tab);
	free_double_pointer(tab);
	return (rgb);
}

char	*check_path(char *str)
{
	char	*path;
	char	c;
	int		i;
	int		fd;

	skip_spaces(str, &i);
	path = ft_strdup(str + i);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) || \
		ft_strlen(path) <= 4)
		exit(puterror("Invalid path: Image extension must be .xpm"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(puterror("Invalid path: File not found"));
	if (read(fd, &c, 0) == -1)
		exit(puterror("Invalid path: File unreadable"));
	close(fd);
	return (path);
}

void	check_map(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_player(map[i][j]))
				count++;
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ' && \
				!is_player(map[i][j]))
				exit(puterror("Invalid map"));
			if ((map[i][j] == '0' || is_player(map[i][j])) && \
				!map_is_valid(map, i, j))
				exit(puterror("Invalid map"));
		}
	}
	if (count != 1)
		exit(puterror("Invalid map"));
}
