#include "get_next_line.h"


int get_next_line(char **line)
{
	static char *s;
	static long long int head, end;		//head:off set   end:end
	static int f;

	int i;
	int tmp;
	char *ret;

	if (f)
	{
		f = 0;
		*line = (char *)malloc(1);
		**line = 0;
		return (0);
	}
	if (!s)		//first time
	{
		s = (char *)malloc(1000000000000);		//enough buffer
		if (!s)
			return (-1);
		tmp = read(0, s, 10000);
		if (!tmp)		//empty file
		{
			free(s);
			s = NULL;
			*line = (char *)malloc(1);
			**line = 0;
			return (0);
		}
		else if (tmp < 0)		//cannot read
		{
			free(s);
			s = NULL;
			*line = NULL;
			return (-1);
		}
		end = tmp;
		while ((tmp = read(0, s + end, 10000)))
			end += tmp;
		s[end] = 0;		//may be not needed		but remember that s[end] == 0
	}
	i = 0;
	while (s[head + i] != '\n' && head + i < end)		//count
		i++;
	ret = (char *)malloc(i + 1);
	i = 0;
	while (s[head + i] != '\n' && head + i < end)
	{
		ret[i] = s[head + i];
		i++;
	}
	ret[i] = 0;
	*line = ret;
	head += i + 1;
	if (head >= end)		//   abc\n\0 -> head == end    abc\0 -> head != end
	{
		free(s);
		s = NULL;
		f = (head == end);
		return (head == end);
	}
	return (1);
}
