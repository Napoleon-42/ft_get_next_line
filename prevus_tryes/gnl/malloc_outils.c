#include "get_next_line.h"

void	f_print(char *str, int back_slash)
{
	int i;

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
	if (back_slash == 1)
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

char	*ft_substr(char *s, unsigned int start)
{
	char	*res;
	int		i;
	int		s_len;

	if (!s)
		return (0);
	s_len = 0;
	while (s[s_len])
		s_len++;
	i = 0;
	if (!(res = malloc((s_len - start) * sizeof(char))))
		return (0);
	while (s[start + i])
	{
		res[i] = s[start + i + 1];
		i++;
	}
	res[i] = 0;
	return (res);
}

int ft_check_str(char *str)
{
	int i;

	i = 0;
	if(str == 0)
		return (BUFFER_SIZE);
	while (i <= BUFFER_SIZE)
	{
		if (str[i] == '\n')
			return (i);
		if (str[i] == '\0')
			return (-1);
		i++;
	}
	return (BUFFER_SIZE);
}

char	*till_n(char *str)
{
	int i;
	char *res;

	while (str[i] != '\n' && str[i])
		i++;
	if(!(res = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int		mem_manage(char **memory, char **line, int *out)
{
	char *temp;

	temp = *memory;
	if (*memory == 0)
		return -1;
	*line = till_n(*memory);
	printf("%d", ft_check_str("y"));
	if (ft_check_str(*memory) == -1)
	{
		free(*memory);
		return 1;
	}
	else
	{
		*memory = ft_substr(*memory, ft_check_str(*memory));
		free(temp);
		return (0);
	}
}

int main(int av, char **ac)
{
	char *memory = 0;
	char **line = 0;
	char *_line = 0;
	line = &_line;
	int	out;

	memory = ft_strdup("Yolo");
	mem_manage(&memory, line, &out);
	f_print(memory, 1);
	f_print(*line, 1);
	return 0;
}