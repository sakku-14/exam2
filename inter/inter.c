#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ft_inter(char *str1, char *str2)
{
	int i = 0;
	int ascii[256] = {0};

	while (str2[i])
	{
		if (ascii[(int)str2[i]] == 0)
			ascii[(int)str2[i]] = 1;
		i++;
	}

	i = 0;
	while (str1[i])
	{
		if (ascii[(int)str1[i]] == 1)
		{
			ascii[(int)str1[i]] = 2;
			write(1, &str1[i], 1);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 3)
		ft_inter(av[1], av[2]);
	return (write(1, "\n", 1));
}
