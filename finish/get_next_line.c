/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:49:18 by lnelson           #+#    #+#             */
/*   Updated: 2020/02/23 13:57:00 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		reader(char *buff, char *memory, int fd)
{
	int res;

	if (memory)
	{
		ft_strcpy(buff, memory);
		free(memory);
		return (1);
	}
	res = read(fd, buff, BUFFER_SIZE);
	buff[res] = 0;
	return (res);
}

int		get_one_line(int i, int fd, char **line, char *buff)
{
	static char	*memory;
	int			res;

	*line = ft_strdup("");
	while ((res = (reader(buff, memory, fd))) > 0)
	{
		if (memory)
			memory = 0;
		if (ft_strrchr(buff, '\n') >= 0)
		{
			i = 0;
			while (buff[i] != '\n')
				i++;
			buff[i] = 0;
			if (!memory)
				memory = ft_strdup(buff + i + 1);
			*line = ft_strjoin(line, buff);
			return (1);
		}
		else
			*line = ft_strjoin(line, buff);
	}
	if (*line == NULL)
		*line = ft_strdup("");
	return (res);
}

int		get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	int			index;
	char		*temp;

	index = 0;
	temp = ft_strdup("");
	if (!line || BUFFER_SIZE < 1 || read(fd, temp, 0) < 0)
		return (-1);
	free(temp);
	temp = 0;
	return (get_one_line(index, fd, line, buff));
}
