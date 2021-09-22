/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:26:58 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/13 16:39:00 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argcheck(int argc, char **argv)
{
	int	i;
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

int	set_error(int *ptr, int err) // or mutex and point to err element in params ... [!!]
{
	*ptr = err;
	return (0);
}

int	ft_printerr(int n)
{
	printf(YELLOW);
	if (n == 1)
	{
		printf("Usage: ./philo <number_of_philosophers> <time_to_die> ");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	else if (n == 2)
		write(2, "Failled to allocate memory!\n", 28);
	else if (n == 3)
		write(2, "Failed to create mutex!\n", 24);
	else if (n == 4)
		write(2, "Failed to create thread!\n", 25);
	else if (n == 5)
		write(2, "pthread_join returned error!\n", 29);
	else if (n == 6)
		write(2, "Failed to destroy mutex!\n", 25);
	else if (n == 7)
		write(2, "gettimeofday returned error!\n", 29);
	else if (n == 8)
		write(2, "Mutex returned error!\n", 22);
	else
	{
		printf(CLR_DFT);
		return (-1);
	}
	printf(CLR_DFT);
	return (n);
}
