# include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	if (58 > c && 47 < c)
		return (42);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long int	n;
	int			j;
	int			neg;

	neg = 1;
	j = 0;
	n = 0;
	while (32 == str[j] || (8 < str[j] && 14 > str[j]))
		j++;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			neg = -1;
		j++;
	}
	while (ft_isdigit(str[j]) && str[j])
	{
		n *= 10;
		n += str[j++] - '0';
	}
	n *= neg;
	if (n < INT_MAX && n > INT_MIN)
		return ((int)n);
	return (0);
}