#include "get_next_line.h"
#include "get_next_line_outils.c"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

char	*ft_bzero(char *s, size_t n)
{
	unsigned char *tmp;

	tmp = (unsigned char*)s;
	while (n > 0)
	{
		*tmp = 0;
		tmp++;
		n--;
	}
	return (s);
}


char	*save(char *str)
{
	static char	*res;
	int			i;
	int			bn_index;

	bn_index = 0;
	i = 0;
	while (str[bn_index] != '\n' && str[bn_index])
		bn_index++;
	res = malloc(sizeof(char) * (ft_strlen(str) - bn_index + 1));
	if (*(str + bn_index + 1) == '\n' && bn_index == 0)
		return (*res = '\0');
	if (res == 0)
		return ("");
	if (bn_index + 1 != '\n')
		bn_index++;
	while (str[bn_index])
	{
		res[i] = str[bn_index];
		i++;
		bn_index++;
	}
	res[i] = 0;
	return (res);
}

int		ft_verif_return(char **memory, char **buff, char **res, int key)
{
	free(*res);
	if (ft_strlen(*buff) != BUFFER_SIZE && ft_check_str(*buff) < 0)
		return (0);
	if (key == 0)
	{
		free(*buff);
		free(*memory);
		return (0);
	}
	free(*buff);
	return (1);
}

int		memory_manage(char **memory)
{
	int i;	

	i = 0;
	if (*memory == 0)
		return (0);
	while (i < ft_strlen(*memory))
	{
		if ((*memory)[i] == '\n')
		{
			*memory = save(*memory);
			return (1);
		}
		i++;
	}
	return(0);
}

int	get_next_line(int fd, char **line)
{
	static char	*memory;
	char		*buff;
	char		*res;
	int			key;
	int i = 0;
	res = 0;
	if (memory != 0)
		res = str_join(&res, memory);
	if (memory_manage(&memory) == 3)
		{
			//write(1, "++ MEMORY ERROR_404 LOL ++");
			return (0);
		}
	if (memory_manage(&memory) == 1)
	{
		//printf("\n\t\t\t\t\t||M_The result: \"%s\" ||", res);
		//printf ("\nMem = |%s|", memory);
		return (1);
	}
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	key = read(fd, buff, BUFFER_SIZE);
	buff[key] = 0;
	while (ft_check_str(buff) == BUFFER_SIZE && ft_strlen(buff) == BUFFER_SIZE && i < 7)
	{
		res = str_join(&res, buff);
		ft_bzero(buff, BUFFER_SIZE);
		key = read(fd, buff, BUFFER_SIZE);
		buff[key] = 0;
		//printf("\n\t\t\t\tturn %d = \t\"%s\"\t\t\t\t\t\t\t\t ||| buff_len = %d :: buff = \"%s\"\n,", i++, res, ft_strlen(buff), buff);
	}
	res = str_join(&res, buff);
	//printf("\n\t\t\t\t\t||  The result: \"%s\" ||", res);
	if (ft_check_str(buff) > 0)
		memory = save(buff);
				i = 0;
				write(1, "\n", 2);
				//write(1, "The memory is: ", 15);
				while (memory[i] != 0)
				{
					if (memory[i] == '\n')
					//	write(1, "\\n", 2);
					else
						write(1, (memory + i), 1);
					i++;
				}
				write(1, "\n", 2);
	*line = res;
	return (ft_verif_return(&memory, &buff, &res, key));
}

int main(int ac, char **av)
{
	char *join_res;
	join_res = 0;
	int i = 1;
	int fd = open("test_fd", O_RDONLY);
	printf("\n\t\t\t\t|| fd check: %d || b_size: %d ||\n\n", fd, BUFFER_SIZE);
	while (i == 1)
	{
		printf("%d", i);
		i = get_next_line(fd, &join_res);
	}
	printf("%d", i);
	

	//printf("ft_check_str return = %d", ft_check_str(" de gnl lol haha"));
	
	printf("\n\n\n\n================================================================================================================\n");

	//printf("my save function result: \"%s\"", save(" aussi?\nHEy salut c la 3eme\nca c"));
	/*join_res = str_join(&join_res, "salut mon pote");
	printf("\n\t\t\t\t||%s||\n", join_res);
	join_res = str_join(&join_res, " ceci est la deuxieme phrase");
	printf("\n\t\t\t\t||%s||\n", join_res);
	free(join_res);*/
	return (0);
}
