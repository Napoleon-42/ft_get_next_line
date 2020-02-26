/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:10:20 by lnelson           #+#    #+#             */
/*   Updated: 2020/02/23 07:18:25 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	f_print(char *start, char *str, int back_slash)
{
	int i;

	i = 0;
	while (start[i])
		write(1, &(start[i++]), 1);
	i = 0;
	write(1, "|", 1);
	while (str[i])
	{
		if (str[i] == '\n')
			write(1, "_\\n_", 4);
		else
			write(1, &(str[i]), 1);
		i++;
	}
	write(1, "|", 1);
	i = 0;
	while (i++ < back_slash)
		write(1, "\n", 1);
	return;
}

char	*ft_strdup(char *c)
{
	char	*tmp;
	int		size;
	char	*res;

	size = 0;
	tmp = (char*)c;
	while (tmp[size])
		size++;
	if (!(res = malloc(sizeof(char) * (size + 1))))
		return (0);
	size = 0;
	while (tmp[size])
	{
		res[size] = tmp[size];
		size++;
	}
	res[size] = 0;
	return (res);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int		ft_strlen(const char *s)
{
	if (s == 0)
		return (0);
	int		res;

	res = 0;
	while (s[res] != 0)
		res++;
	return (res);
}


int		ft_check_str(char *str)
{
	int i;

	i = 0;
	if(str == 0)
		return (-2147483648);
	while (i < BUFFER_SIZE)
	{
		if (str[i])
			if (str[i] == '\n')
				return (i);
		i++;
	}
	return (-1);
}

int		join(char **line, char *str)
{
	char	*temp;
	int		i;
	int		n_index;

	i = 0;
	n_index = 0;
	while (str[n_index] != 0 && str[n_index] != '\n')
		n_index++;
	if (!(temp = malloc(sizeof(char) * (ft_strlen(*line) + n_index + 1))))
		return (-1);
	i = 0;
	while (i < (ft_strlen(*line) + n_index))
	{
		if (i < ft_strlen(*line))
			temp[i] = (*line)[i];
		else
			temp[i] = str[i - ft_strlen(*line)];
		i++;
	}
	temp[i] = 0;
	free(*line);
	*line = temp;
	return (0);
}

int		reader(int *reader_key, char *memory, char **line, int fd)
{
	char *buff;

	buff = 0;
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	*reader_key = read(fd, buff, BUFFER_SIZE);
	if (*reader_key == 0)
		return (42);
	buff[*reader_key] = 0;
	while (ft_check_str(buff) == -1 && ft_strlen(buff) == BUFFER_SIZE)
	{
		//f_print("\nBUFFER == ", buff, 1);
		join(line, buff);
		*reader_key = read(fd, buff, BUFFER_SIZE);
		buff[*reader_key] = 0;
	}
//	f_print("\nBUFFER == ", buff, 1);
	join(line, buff);
	save_memo(memory, buff);
	//f_print("memory =", memory, 2);
	free(buff);
	return (0);
}

int		trim_memo(char *memory)
{
	int i;
	int n_index;

	i = 0;
	n_index = ft_check_str(memory);
	n_index++;
	while (i < BUFFER_SIZE)
	{
		if (n_index < 0)
			memory[i] = 0;
		else
		{
			if (i + n_index < BUFFER_SIZE)
				memory[i] = memory[i + n_index];
			else
				memory[i] = 0;
		}
		i++;
	}
	return (0);
}

int		memory_reader(int *reader_key, char *memory, char **line, int fd)
{
	if (ft_check_str(memory) == -1)
	{
		join(line, memory);
		trim_memo(memory);
		return (1);
	}
	else
	{
		join(line, memory);
		trim_memo(memory);
		if (reader(reader_key, memory, line, fd) == -1)
			return (-1);
		return (0);
	}
	return (-1);
}

int		ft_exit(char **str, int key)
{
	if (str)
	{
		free(*str);
		*str = 0;
	}
	return (key);
}

int		save_memo(char *memory, char *buffer)
{
	int i;
	int n_index;

	n_index = ft_check_str(buffer);
	i = 0;
	if (n_index < 0)
		while (i < BUFFER_SIZE)
		{
			memory[i] = buffer[i];
			i++;
		}
	else
	{
		n_index++;
		while (i < BUFFER_SIZE)
		{
			if (i + n_index < BUFFER_SIZE)
				memory[i] = buffer[n_index + i];
			else
				memory[i] = 0;
			i++;
		}
	}
	return (0);
}
/*
int main(int av, char **ac)
{
	char *test_line;
	char *line;
	char *buff;
	char *memory;
	buff = malloc(sizeof(char ) * BUFFER_SIZE + 1);
	memory = malloc(sizeof(char) * BUFFER_SIZE + 1);
	int i;
	
	//			READER CHECK MTFC
	int fd = open("fd_test", O_RDONLY);
	return 0;
}
*/
