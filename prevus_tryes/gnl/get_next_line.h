#ifndef __GET_NEXT_LINE_H_
# define __GET_NEXT_LINE_H_
# define BUFFER_SIZE 100
# define F_MEMORY 2
# define READ_FINISH 1
# define MEMORY_READ_FINISH 0
# define READING 42
# include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef	struct	s_mem
{
	char	*str;
	char	reader_key;
	int		return_key;
	char	n_status;
	int		str_size;
	int		buff_size;
	int		index_fn;
}				t_sring;


int		join(char **line, t_sring *buff);
int		malloc_spring(t_sring **ptr, int type_key);
int		check_str(t_sring *str);
int		reader(t_sring *memory, t_sring *buff, char **line, int fd);
int		read_memory(t_sring *memory, char **line);
void	free_buff(t_sring **buff);
int		save_freeb(t_sring *memory, t_sring *buff);
void	cut_mem(t_sring *memory);
int		get_next_line_start(t_sring *memory, t_sring *buff, int fd, char **line);


#endif
