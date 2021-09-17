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
		p[i].state = THINKING;
		p[i].timings = params->timings;
		// p[i].last_meal = 0;
		p[i].meals_eaten = 0;
		params->fork[i].is_taken = 0;
		p[i].r_fork = &params->fork[i];
		p[i].l_fork = &params->fork[(i + 1) % params->philo_num]; // !!
		p[i].g_lock = &params->general_lock;
		p[i].nobody_died = &params->nobody_died;
	}
	// p[i - 1].l_fork = &params->fork[0];
	return (p);
}

t_philo	*init_structs(char **argv, t_params *params)
/*2 forks for 1 philosopher case*/
{
	params->philo_num = ft_atoi(argv[1]);
	params->timings.dead_time = ft_atoi(argv[2]);
	params->timings.meal_time = ft_atoi(argv[3]);
	params->timings.sleep_time = ft_atoi(argv[4]);
	params->nobody_died = 1;
	if (argv[5])
		params->timings.num_meals = ft_atoi(argv[5]);
	else
		params->timings.num_meals = 0;
	// allocating memory for array of philosophers and t_mutex structs aka forks and checking for success
	params->fork = calloc(params->philo_num, sizeof(t_fork));
	if (!params->fork)
		return (NULL);
	
	// while (params->timings.init_t <= 0) // retry in case of error. init_t won't be same for all threads !!
	// 	params->timings.init_t = ft_gettime();

	// initializing philosophers infos
	return (init_philo(params));
}

bool	mutex_init(t_params *params, t_philo *philo, int i)
{
	if (pthread_mutex_init(&params->general_lock, NULL))
	{
		free(philo);
		free(params->fork);
		return (0);
	}
	while (++i < params->philo_num)
	{
		if (pthread_mutex_init(&params->fork[i].lock, NULL))
		{
			free(philo);
			free(params->fork);
			return (0);
		}
	}
	return (1);
}

int	free_everything(t_params *params, t_philo *philo, int i)
{
	int	ret;

	ret = 0;
	pthread_mutex_destroy(&params->general_lock);
	while (++i < params->philo_num)
	{
		if (pthread_mutex_destroy(&params->fork[i].lock))
		{
			// i--; // retry or return error ??
			ret = 6;
		}
	}
	free(philo);
	free(params->fork);
	return (ret);
}
