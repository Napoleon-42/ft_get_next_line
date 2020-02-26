/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:06:33 by lnelson           #+#    #+#             */
/*   Updated: 2020/02/23 07:21:30 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char	*memory;
	int			fd_status;
	int			tmp;

	fd_status = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ft_exit(&memory, -1));
	if (!(*line = malloc(sizeof(char) * 1)))
		return (ft_exit(&memory, -1));
	*line = 0;
	if (!memory)
	{
	//	write(1, "--------NO MEMORY-------\n", 25);
		if (!(memory = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		memory[0] = 0;
		if (reader(&fd_status, memory, line, fd) == -1)
			return (ft_exit(&memory, -1));
	}
	else
	{
		//write(1, "--------MEMORY-------\n", 22);
		//f_print("memory =", memory, 2);
		tmp = memory_reader(&fd_status, memory, line, fd);
		if (tmp == -1)
			return (ft_exit(&memory, -1));
		else if(tmp == 0)
			return(1);
		else
			if(reader(&fd_status, memory, line, fd) == -1)
				return (ft_exit(&memory, -1));
	}
	if (fd_status == 0 && *memory == 0)
		return (ft_exit(&memory, 0));
	return (1);
}


// int main(int ac, char **av)
// {
// 	char *line;
// 	line = 0;
// 	int i = 1;
// 	int counter = 1;
// 	int fd = open("fd_test", O_RDONLY);
// 	printf("\033[0;33m\n\t\t\t\t|| fd check: %d || b_size: %d ||\033[0m\n\n", fd, BUFFER_SIZE);
// 	while (i == 1)
// 	{
// 		i = get_next_line(fd, &line);
// 		printf("\033[0;33mphrase  |  {%d}  |  \033[0m", counter);
// 		printf("\033[0;31m{-%s-}	|\033[0m\n", line);
// 		counter++;
// 	}
// 	printf("\n\t\t\t%d", i);
// 	return (0);
// }
/*
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    int fd;
	int u;
	int i = 1;
    char *line;

    fd = open("fichier.txt", O_RDONLY);

    while((u = get_next_line(fd, &line)) != 0)
	{
		if (u == -1)
			return (-1);
		printf("\033[31m[LIGNE %d GNL=%d] : %s\n\033[0m",i,u, line);
		free(line);	
		i++;
	}
    u = get_next_line(fd, &line);
	free(line);
    printf("\033[31m[LIGNE %d GNL=%d] : %s\n\033[0m\n\n>>>         TOTAL LIGNES : %d\n\n",i,u, line, i);
    system("leaks a.out");
	return(0);
}*/
