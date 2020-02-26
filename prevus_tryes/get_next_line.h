#ifndef __GET_NEXT_LINE_H_
# define __GET_NEXT_LINE_H_
# define BUFFER_SIZE 1
# define F_MEMORY 1
# include <stdlib.h>

int	ft_strlen(const char *s);
int		ft_verif_return(char **memory, char **buff, char **res, int key);
int		get_next_line(int fd, char **line);
int		ft_check_str(char *str);
char	*str_join(char **start_line, char *b_line);
int		ft_strlen(const char *s);

#endif
