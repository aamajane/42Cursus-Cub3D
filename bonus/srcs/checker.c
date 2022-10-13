/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:42:50 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/07 02:46:58 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char	*ft_strdupl(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
* PROTECT AGAINST HIDDEN FILE
*/

void	checker(t_elm *elm, char *arg)
{
	char	**file;
	int		i;
	char 	*tmp;

	tmp = ft_strdupl(arg);
	ft_strrev(tmp);
	//Printf("tmp = %s\n", tmp);
	//printf("%c\n", tmp[4]);
	if (tmp[3] == '.' && tmp[4] == '/')
	{
		//write(2, "hi\n", 2);
		free(tmp);
		exit(puterror("Invalid file extension"));
	}
	if (ft_strncmp(tmp, "buc.", 4) != 0x0)
	{
		free(tmp);
		exit(puterror("file extension must be .cub"));
	}
	file = read_file(arg);
	elm->map_width = map_width(file);
	elm->map_height = map_height(file);
	elm->map = (char **)ft_calloc(elm->map_height + 1, sizeof(char *));
	i = -1;
	while (file[++i])
	{
		elm->map[i] = (char *)ft_calloc(elm->map_width + 1, sizeof(char));
		ft_strlcpy(elm->map[i], file[i], ft_strlen(file[i]) + 1);
	}
	elm->map[i] = NULL;
	free_double_pointer(file);
	check_map(elm->map);
	free(tmp);
}

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
				map[i][j] != 'd' && map[i][j] != 's' && !is_player(map[i][j]))
				exit(puterror("Invalid map"));
			if ((map[i][j] == '0' || map[i][j] == 'd' || \
				map[i][j] == 's' || is_player(map[i][j])) \
				&& (!i || !map[i + 1] || !j || !map[i][j + 1] || \
				map[i][j + 1] == ' ' || (j && map[i][j - 1] == ' ')))
				exit(puterror("Invalid map"));
		}
	}
	if (count != 1)
		exit(puterror("Invalid map"));
}

int	map_width(char **map)
{
	int	width;
	int	i;
	int	j;

	width = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > width)
			width = j;
		i++;
	}
	return (width);
}

int	map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	return (height);
}
