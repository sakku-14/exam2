#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int minfield;
int vadigit;
int p;
int i;
int ret;
char conversion;

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
	ret++;
}

void ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

char *ft_itoa(long n, int base)
{
	char *s;
	long x;
	int i;
	x = n;
	i = 1;
	while (x / base != 0)
	{
		x /= base;
		i++;
	}
	s = malloc(i + 1);
	s[i] = '\0';
	for (int j = i - 1; j >= 0 ; j--)
	{
		if (base == 10)
		{
			s[j] = "0123456789"[n % base];
			n /= base;
		}
		else if (base == 16)
		{
			s[j] = "0123456789abcdef"[n % base];
			n /= base;
		}
	}
	return (s);
}

void ft_conv(va_list ap)
{
	if (conversion == 'd')
	{
		char *s;
		int sign;
		int nb;
		int len;
		nb = va_arg(ap, int);
		sign = (nb < 0) ? 1 : 0;
		nb *= (sign) ? -1 : 1;
		s = ft_itoa(nb, 10);
		len = (sign) ? ft_strlen(s) + 1 : ft_strlen(s);
		(p == 1 && vadigit == 0 && nb == 0) ? len = 0 : len;
		while (minfield > len && minfield > vadigit)
		{
			ft_putchar(' ');
			minfield--;
		}
		len = (sign < 0) ? len - 1 : len;
		(sign) ? ft_putchar('-') : 0;
		while (vadigit > len)
		{
			ft_putchar('0');
			vadigit--;
		}
		(len) ? ft_putstr(s) : 0;
	}
	if (conversion == 's')
	{
		char *s;
		int len;
		s = va_arg(ap, char *);
		len = ft_strlen(s);
		(vadigit == 0 && p == 1) ? len = vadigit : len;
		(vadigit != 0 && vadigit < len) ? len = vadigit : len;
		while (minfield > len)
		{
			ft_putchar(' ');
			minfield--;
		}
		for (int i = 0; i < len; i++)
		{
			ft_putchar(s[i]);
		}
	}
	if (conversion == 'x')
	{
		char *s;
		unsigned int nb;
		int len;
		nb = va_arg(ap, unsigned int);
		s = ft_itoa(nb, 16);
		len = ft_strlen(s);
		(p == 1 && vadigit == 0 && nb == 0) ? len = 0 : len;
		while (minfield > len && minfield > vadigit)
		{
			ft_putchar(' ');
			minfield--;
		}
		while (vadigit > len)
		{
			ft_putchar('0');
			vadigit--;
		}
		(len) ? ft_putstr(s) : 0;
	}
}

void ft_print(va_list ap, const char *s)
{
	minfield = 0;
	vadigit = 0;
	if (s[i] == '%')
	{
		ft_putchar('%');
		i++;
		return ;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		minfield = minfield * 10 + s[i] - '0';
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		p = 1;
		while (s[i] >= '0' && s[i] <= '9')
		{
			vadigit = vadigit * 10 + s[i] - '0';
			i++;
		}
	}
	conversion = s[i++];
	ft_conv(ap);
}

int ft_printf(const char *s, ...)
{
	va_list ap;
	ret = 0;
	i = 0;
	va_start(ap, s);

	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ft_print(ap, s);
		}
		else if (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
	va_end(ap);
	return (ret);
}

int main()
{
	int d = ft_printf("%10.3d\n%10.3s\n%10.3x\n", 55555, "55555", 55555);
	ft_printf("%d\n", d);
}
