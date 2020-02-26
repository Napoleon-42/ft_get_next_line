/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:32:10 by lnelson           #+#    #+#             */
/*   Updated: 2020/02/19 18:33:41 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

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

int		join(char **line, t_sring *buff)
{
	int 	l_size;
	int 	f_size;
	int 	i;
	char	*temp;

	i = 0;
	l_size = 0;
	while ((*line)[l_size])
		l_size++;
	f_size = l_size + (buff->index_fn == -1 ? buff->str_size : buff->index_fn);
	if (!(temp = malloc(sizeof(char) * (f_size + 1))))
		return (-1);
	while (i < f_size)
	{
		if (i < l_size)
			temp[i] = (*line)[i];
		else
			temp[i] = buff->str[i - l_size];
		i++;
	}
	temp[f_size] = 0;
	free(*line);
	*line = temp;
	return (1);
}

int		malloc_spring(t_sring **ptr, int type_key)
{
	if (*ptr == 0)
	{
		if(!(*ptr = malloc(sizeof(t_sring))))
			return (-1);
	}
	else
		return (0);
	if (type_key == 2)
	{
		(*ptr)->reader_key = 40;
		(*ptr)->return_key = 1;
		if(!((**ptr).str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		(**ptr).buff_size = BUFFER_SIZE + 1;
		(**ptr).str_size = BUFFER_SIZE;
	}
	(**ptr).n_status = 0;
	(**ptr).index_fn = -1;
	return (0);
}

int		check_str(t_sring *str)
{
	int i;
	char n_key;

	if (str->str == 0)
		return (-1);
	i = 0;
	n_key = 0;
	str->n_status = 0;
	str->index_fn = -1;
	while (i < str->str_size)
	{
		if (str->str[i] == '\n')
		{
			n_key = 1;
			str->n_status++;
			if (str->n_status == 2)
				return (1);
			str->index_fn = i;
		}
		i++;
	}
	if (n_key == 0)
		return (-1);
	return (1);
}

int		reader(t_sring *memory, t_sring *buff, char **line, int fd)
{
	int i;
	int k;

	i = 0;
	while (check_str(buff) != 1 && buff->str_size != 0)
	{
		buff->str_size = read(fd, buff->str, BUFFER_SIZE);
		check_str(buff);
		if(join(line, buff) == -1)
			return (-1);
	}
	if (join(line, buff) == -1)
		return (-1);
	if (buff->str_size == 0)
		memory->reader_key = READ_FINISH;
	return (1);
}

void	free_buff(t_sring **buff)
{
	free((*buff)->str);
	free(*buff);
	return ;
}

int		save_freeb(t_sring *memory, t_sring *buff)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if (buff->str_size > 0 && buff->str_size < BUFFER_SIZE)
		while (i < buff->str[i])
		{
			memory->str[i] = buff->str[i];
			i++;
		}
	else if (buff->str_size == BUFFER_SIZE)
	{
		while (buff->str[k] != '\n' && k < buff->buff_size)
			k++;
		while (i < buff->buff_size)
		{
			memory->str[i] = buff->str[k];
			k++;
			i++;
		}
	}
	while (i < memory->buff_size)
		memory->str[++i] = 0;
	free_buff(&buff);
	return (1);
}

void	cut_mem(t_sring *memory)
{
	int i;

	i = 0;
	if (memory->index_fn != -1)
		while (i < (memory->str_size - memory->index_fn))
		{
			memory->str[i] = memory->str[i + memory->index_fn];
			i++;
		}
	while (i < memory->buff_size)
	{
		memory->str[i] = 0;
		i++;
	}
	return ;
}

int		read_memory(t_sring *memory, char **line)
{
	int i;

	i = 0;
	check_str(memory);
	if(join(line, memory) == -1)
		return (-1);
	return (0);
}

int	get_next_line_start(t_sring *memory, t_sring *buff, int fd, char **line)
{

	if (memory == 0)
	{
		malloc_spring(&memory, 2);
		malloc_spring(&buff, 2);
	}
	else
	{
		if (check_str(memory) != -1)
		{
			if (read_memory(memory, line) == -1)
				return (-1);
			cut_mem(memory);
			malloc_spring(&buff, 2);
		}
		else
		{
			if (read_memory(memory, line) == -1)
				return (-1);
			cut_mem(memory);
			return (1);
		}
	}
	return (0);
}
/*
int main(int av, char **ac)
{
	int fd;
	t_sring	*memory;
	t_sring *buff;
	malloc_spring(&memory, 2);
	malloc_spring(&buff, 2);
	char *line;
	line= malloc(sizeof(char) * 1);
	line[0] = 0;
	char *test_line;
//	buff+memory+line->0

//			FD OPEN + READER / SAVER TESTS

	fd = open("./fd_test", O_RDONLY);
	reader(memory, buff, &line, fd);
	f_print("line is =", line, 2);
	f_print("buff is =", buff->str, 2);
	save_freeb(memory, buff);
	f_print("memo is =", memory->str, 2);


	memory->str = ft_strdup("salut ceci est un test numero 1");
	f_print("memo is =", memory->str, 2);
	check_str(memory);
	read_memory(memory, &line);
	f_print("line is =", line, 2);
	f_print("memo is =", memory->str, 4);

	free(line);
	line= malloc(sizeof(char) * 1);
	line[0] = 0;
	memory->str = ft_strdup("salut ceci est un test numero 2_\n enfaine ouais");
	f_print("memo is =", memory->str, 2);
	check_str(memory);
	read_memory(memory, &line);
	f_print("line is =", line, 2);
	f_print("memo is =", memory->str, 2);

}
*/
/*	malloc_spring keys:
**	1 = memory
**	2 = buffer
*/