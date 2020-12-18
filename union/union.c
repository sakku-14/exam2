#include <unistd.h>

void ft_union(char *first, char *second)
{
	int i = 0;
	int ascii[256] = {0};

	while (first[i])
	{
		if (ascii[(int)first[i]] == 0)
			ascii[(int)first[i]] = 1;
		i++;
	}
	i = 0;
	while (first[i])
	{
		if (ascii[(int)first[i]] == 1)
		{
			ascii[(int)first[i]] = 2;
			write(1, &first[i], 1);
		}
		i++;
	}
	i = 0;
	while (second[i])
	{
		if (ascii[(int)second[i]] == 0)
			ascii[(int)second[i]] = 1;
		i++;
	}
	i = 0;
	while (second[i])
	{
		if (ascii[(int)second[i]] == 1)
		{
			ascii[(int)second[i]] = 2;
			write(1, &second[i], 1);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 3)
		ft_union(av[1], av[2]);
	return (write(1, "\n", 1));
}
