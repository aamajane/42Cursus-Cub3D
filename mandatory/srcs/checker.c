/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:42:50 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/14 23:17:06 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	checker(t_elm *elm, char *arg)
{
	char	**tmp_elm;
	char	**file;
	t_var	var;

	if (ft_strncmp(arg + ft_strlen(arg) - 4, ".cub", 4) || ft_strlen(arg) <= 4)
		exit(puterror("file extension must be .cub"));
	file = read_file(arg);
	separate_file_elements(elm, &tmp_elm, file);
	free_double_pointer(file);
	elm->path = (char **)malloc(sizeof(char *) * 4);
	elm->rgb = (int **)malloc(sizeof(int *) * 2);
	check_elements(elm, &var, tmp_elm);
	free_double_pointer(tmp_elm);
	elm->floor_color = \
				create_trgb(0, elm->rgb[0][0], elm->rgb[0][1], elm->rgb[0][2]);
	elm->ceiling_color = \
				create_trgb(0, elm->rgb[1][0], elm->rgb[1][1], elm->rgb[1][2]);
}

void	check_elements(t_elm *elm, t_var *var, char **tmp_elm)
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
			elm->rgb[color] = check_color(var, tmp_elm[i] + j + 2);
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

int	*check_color(t_var *var, char *str)
{
	skip_spaces(str, &var->i);
	if (commas_number(str + var->i) != 2)
		exit(puterror("Invalid color format"));
	var->tab = ft_split(str + var->i, ',');
	var->i = -1;
	while (var->tab[++var->i])
	{
		if (!var->tab[var->i][var->j] || \
			ft_strlen(var->tab[var->i] + var->j) > 3)
			exit(puterror("Invalid color"));
		while (var->tab[var->i][var->j])
			if (!ft_isdigit(var->tab[var->i][var->j++]))
				exit(puterror("Invalid color"));
	}
	if (var->i != 3)
		exit(puterror("Invalid color"));
	var->rgb = copy_rgb_color(var->tab);
	free_double_pointer(var->tab);
	return (var->rgb);
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
				(!i || !map[i + 1] || !j || !map[i][j + 1] || \
				map[i][j + 1] == ' ' || (j && map[i][j - 1] == ' ') || \
				map[i + 1][j] == ' ' || (i && map[i - 1][j] == ' ')))
				exit(puterror("Invalid map"));
		}
	}
	if (count != 1)
		exit(puterror("Invalid map"));
}
