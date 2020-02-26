#ifndef __GET_NEXT_LINE_H_
# define __GET_NEXT_LINE_H_

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		ft_strlen(const char *s);
int		ft_check_str(char *str);
int		join(char **line, char *str);
int		reader(int *reader_key, char *memory, char **line, int fd);
int		trim_memo(char *memory);
int		memory_reader(int *reader_key, char *memory, char **line, int fd);
int		save_memo(char *memory, char *buffer);
int		get_next_line(int fd, char **line);
int		ft_exit(char **str, int key);
char	*ft_strdup(char *c);

#endif
