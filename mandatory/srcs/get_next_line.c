/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:05:30 by aamajane          #+#    #+#             */
/*   Updated: 2022/09/07 18:34:51 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#define BUF_SIZE 10

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	char		*buf;

	if (fd < 0 || BUF_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(*buf) * (BUF_SIZE + 1));
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		get_free(&buf);
		return (NULL);
	}
	if (!stock)
		stock = ft_strdup("");
	get_file(fd, &stock, &line, &buf);
	return (line);
}

void	get_file(int fd, char **stock, char **line, char **buf)
{
	ssize_t	ret;
	char	*temp;

	ret = 1;
	while (ret && !ft_strchr(*stock, '\n'))
	{
		ret = read(fd, *buf, BUF_SIZE);
		(*buf)[ret] = '\0';
		temp = *stock;
		*stock = ft_strjoin(temp, *buf);
		get_free(&temp);
	}
	get_free(buf);
	*stock = get_line(stock, line);
}

char	*get_line(char **stock, char **line)
{
	int		i;
	char	*new_stock;

	i = 0;
	new_stock = NULL;
	while (*(*stock + i) != '\n' && *(*stock + i) != '\0')
		i++;
	if (*(*stock + i) == '\n')
	{
		*line = ft_substr(*stock, 0, ++i);
		new_stock = ft_strdup(*stock + i);
	}
	else
		*line = ft_strdup(*stock);
	get_free(stock);
	if (**line == '\0')
		get_free(line);
	return (new_stock);
}

void	get_free(char **str)
{
	free(*str);
	*str = NULL;
}
