#include "../inc/philo.h"

int	argcheck(int argc, char **argv)
{
	int i;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!argv[i][j])
				break ;
			if (!ft_isdigit(argv[i][j++]))
				return (0);
		}
	}
	return (1);
}