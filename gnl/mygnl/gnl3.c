#include "gnl3.h"

int get_next_line(char **line)
{
	static char *s;
	static long long int head, end;
	static int f;
	int i, tmp;
	char *ret;

	if (f)
	{
		*line = malloc(1);
		**line = 0;
		return (0);
	}
	if (!s)
	{
		if (!(s = malloc(1000000000000)))
			return (-1);
		tmp = read(0, s, 10000);
		if (tmp < 0)
		{
			free(s);
			s = NULL;
			*line = NULL;
			return (-1);
		}
		if (tmp == 0)
		{
			free(s);
			s = NULL;
			*line = malloc(1);
			**line = 0;
			return (0);
		}
		end = tmp;
		while ((tmp = read(0, s + end, 10000)))
			end += tmp;
		s[end] = 0;
	}
	i = 0;
	while (s[head + i] != '\n' && head + i < end)
		i++;
	ret = malloc(i + 1);
	i = 0;
	while (s[head + i] != '\n' && head + i < end)
	{
		ret[i] = s[head + i];
		i++;
	}
	ret[i] = 0;
	*line = ret;
	head += i + 1;
	if (head >= end)
	{
		free(s);
		s = NULL;
		f = (head == end);
		return ((head == end));
	}
	return (1);
}

int main()
{
	char *line;
	int d;
	d = get_next_line(&line);
	while (d)
	{
		printf("\nret=%d...line=\"%s\"\n", d, line);
		d = get_next_line(&line);
		if (!d)
			printf("\nret=%d...line=\"%s\"\n", d, line);
	}
}
