/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 10:49:24 by lnelson           #+#    #+#             */
/*   Updated: 2020/02/23 13:57:08 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin(char **line, char *buff);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strlen(const char *s);
int		ft_strrchr(const char *s, int c);
int		reader(char *buff, char *memory, int fd);
int		get_next_line(int fd, char **line);
int		get_one_line(int i, int fd, char **line, char *buff);

#endif
