/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:35:25 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/01 16:35:28 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_error.h"

static t_philo	*init_philo(t_params *params)
{
	t_philo	*p;
	int		i;

	i = -1;
	p = calloc(params->philo_num, sizeof(t_philo));
	if (!p)
	{
		free(params);
		return (NULL);
	}
	while (++i < params->philo_num)
	{
		p[i].N = i + 1;
		// p[i].state = THINKING;
		p[i].timings = params->timings;
		p[i].meals_eaten = 0;
		params->fork[i].is_taken = 0;
		p[i].r_fork = &params->fork[i];
		p[i].l_fork = &params->fork[(i + 1) % params->philo_num];
		p[i].printlock = &params->printlock;
		p[i].deathlock = &params->deathlock;
		p[i].someone_died = &params->someone_died;
		p[i].err = &params->retnum;
	}
	return (p);
}

t_philo	*init_structs(char **argv, t_params *params)
/*2 forks for 1 philosopher case*/
{
	params->philo_num = ft_atoi(argv[1]);
	params->timings.dead_time = ft_atoi(argv[2]);
	params->timings.meal_time = ft_atoi(argv[3]);
	params->timings.sleep_time = ft_atoi(argv[4]);
	params->someone_died = 0;
	params->retnum = 0;
	if (argv[5])
		params->timings.num_meals = ft_atoi(argv[5]);
	else
		params->timings.num_meals = 0;
	// allocating memory for array of philosophers and t_mutex structs aka forks and checking for success
	params->fork = calloc(params->philo_num, sizeof(t_fork));
	if (!params->fork)
		return (NULL);
	// initializing philosophers infos
	return (init_philo(params));
}

bool	mutex_init(t_params *params, t_philo *philo, int i)
{
	if (pthread_mutex_init(&params->printlock, NULL))
	{
		free(philo);
		free(params->fork);
		return (0);
	}
	if (pthread_mutex_init(&params->deathlock, NULL))
	{
		pthread_mutex_destroy(&params->printlock);
		free(philo);
		free(params->fork);
		return (0);
	}
	while (++i < params->philo_num)
	{
		if (pthread_mutex_init(&params->fork[i].lock, NULL))
		{
			pthread_mutex_destroy(&params->printlock);
			pthread_mutex_destroy(&params->deathlock);
			free(philo);
			free(params->fork);
			return (0);
		}
	}
	return (1);
}

int	free_everything(t_params *params, t_philo *philo, int i, int ret)
{
	ret = pthread_mutex_destroy(&params->printlock);
	ret = pthread_mutex_destroy(&params->deathlock);
	/*-------DEBUGGING-------*/
	printf("ERROR g_lock %d\n", ret);
	/*-------DEBUGGING-------*/

	while (++i < params->philo_num)
	{
		ret = pthread_mutex_destroy(&params->fork[i].lock);
		/*-------DEBUGGING-------*/
		printf ("ERROR %d\n", ret);
		if (ret)
			ret = 6;
		/*-------DEBUGGING-------*/
	}
	free(philo);
	free(params->fork);
	return (ret);
}

int	init_threads(int philo_num, t_philo *philo, int i)
{
	// void	*ret;

	while (++i < philo_num)
	{
		if (pthread_create(&philo[i].th, NULL, &ft_thread, &philo[i]))
			return (4);
	}
	i = -1;
	while (++i < philo_num)
	{
		if (pthread_join(philo[i].th, NULL/*&ret*/))
			return (5);
	}
	return (0);/*(*(int *)ret);*/
}