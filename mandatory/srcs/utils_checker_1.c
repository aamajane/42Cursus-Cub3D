/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:29:52 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/16 16:51:27 by aamajane         ###   ########.fr       */
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

void	skip_spaces(char *str, int *i)
{
	*i = 0;
	while (str[*i] == ' ')
		(*i)++;
}

int	map_is_valid(char **map, int i, int j)
{
	if (!i || !map[i + 1] || !map[i + 1][j] || (i && !map[i - 1][j]) || \
		!j || !map[i][j + 1] || (j && !map[i][j - 1]) || \
		map[i + 1][j] == ' ' || (i && map[i - 1][j] == ' ') || \
		map[i][j + 1] == ' ' || (j && map[i][j - 1] == ' '))
		return (0);
	return (1);
}
