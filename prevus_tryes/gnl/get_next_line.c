#include "get_next_line.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int		get_next_line(int fd, char **line)
{
	static t_sring	*memory;
	t_sring			*buffer;
	int tmp;

	tmp = get_next_line_start(memory, buffer, fd, line);
	if (tmp == -1 || tmp == 1)
		return (tmp);
	reader(memory, buffer, line, fd);
	save_freeb(memory, buffer);
	return (1);
}

int main(int ac, char **av)
{
	int fd = open("./fd_test", O_RDONLY);
	char *line;
	get_next_line(fd, &line);
	return (0);
}