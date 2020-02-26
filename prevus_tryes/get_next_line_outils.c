#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int		res;

	res = 0;
	while (s[res] != 0)
		res++;
	return (res);
}

void	get_all_sizes(char const *s1, char const *s2, int *res)
{
	int i;

	res[0] = 0;
	res[1] = 0;
	i = 0;
	while (s1[i])
	{
		res[0]++;
		res[1]++;
		i++;
	}
	i = 0;
	while (s2[i] != '\n' && s2[i] && i < res[0] + BUFFER_SIZE)
	{
		res[1]++;
		i++;
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		sizes[2];
	char	*res;

	if (!s1 || !s2)
		return (0);
	i = 0;
	get_all_sizes(s1, s2, sizes);
	if (!(res = malloc((sizes[1] + 1) * sizeof(char))))
		return (NULL);
	res[sizes[1]] = 0;
	while (i < sizes[1])
	{
		if (i < sizes[0])
			res[i] = s1[i];
		else
			res[i] = s2[i - sizes[0]];
		i++;
	}
	return (res);
}

int ft_check_str(char *str)
{
	int i;

	i = 0;
	if(str == 0)
		return (BUFFER_SIZE);
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\n')
			return (i);
		if (str[i] == '\0')
			return (-i);
		i++;
	}
	return (BUFFER_SIZE);
}

char	*str_join(char **start_line, char *b_line)
{
	char *res;
	int i;
	int sl_size;
	int b_size;

	b_size = (ft_check_str(b_line) > 0) ? ft_check_str(b_line) : -ft_check_str(b_line);
	if (*start_line == 0)
	{
		res = malloc((b_size + 1) * sizeof(char));
		i = 0;
		while (i < b_size)
		{
			res[i] = b_line[i];
			i++;
		}
		res[b_size] = 0;
		return (res);
	}
	res = ft_strjoin(*start_line, b_line);
	free(*start_line);
	*start_line = 0;
	return (res);
}