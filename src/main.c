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

#include "../inc/philo.h"

t_philo	*init_structs(char **argv, t_params *params, int i)
/*	UPDATE LINE NUMS <------------------------------- TOO MANY LINES!!!!!!!!
	2 forks for 1 philosopher case*/
{
	t_philo	*p; //return value

	// initializing w/ arg values
	params->philo_num = ft_atoi(argv[1]);
	params->timings.dead_time = ft_atoi(argv[2]);
	params->timings.meal_time = ft_atoi(argv[3]);
	params->timings.sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		params->timings.num_meals = ft_atoi(argv[5]);
	else
		params->timings.num_meals = -1;
	
	// allocating memory for array of philosophers and t_mutex structs aka forks and checking for success
	p = calloc(params->philo_num, sizeof(t_philo));
	if (!p)
		return (NULL);
	params->fork = calloc(params->philo_num, sizeof(t_fork));
	if (!params->fork)
	{
		free(p);
		return (NULL);
	}

	// initializing philosophers infos
	while (++i < params->philo_num)
	{
		p[i].N = i + 1;
		params->fork[i].is_taken = 0;
		p[i].timings = params->timings;
		p[i].r_fork = &params->fork[i];
		p[i].l_fork = &params->fork[i + 1];
		p[i].last_meal = 0; // ??
	}
	p[i - 1].l_fork = &params->fork[0];
	return (p);
}

int	main(int argc, char **argv)
{
	t_philo		*philo; // unnecessary if params points to a philo struct already (.p)
	t_params	params;
	int			i;

	philo = NULL;
	i = -1;
	// early err checking
	if (!argcheck(argc, argv)) //not working
		return (ft_printerr(1));
	// initializing arguments
	philo = init_structs(argv, &params, i); // i for saving lines
	if (!philo)
		return (ft_printerr(2));
	// creating mutexes
	while (++i < params.philo_num)
	{
		if (pthread_mutex_init(&params.fork[i].lock, NULL))
		{
			free(philo);
			free(params.fork);
			return (ft_printerr(3));
		}
	}
	//creating threads
	i = -1;
	while (++i < params.philo_num)
	{
		philo->state = THINKING;
		if (pthread_create(&philo[i].th, NULL, &ft_thread, &philo[i]))
		{
			free(philo);
			free(params.fork);
			return (ft_printerr(4));
		}
	}


	/*3rd loop to keep main thread going in the background so struct params can manage queue and stuff??? (thread_detach)
	
	detach threads

	while (nobody_died(philo, params.philo.num)) // faster than 10us ?? or just print outside this thread
	{

		manage queue
		(or check if someone has returned: pthread_join(th, &bufferforphilonum))
	}
	// release memory; threads already detached
	// send "signal" to threads??
	*/


	i = -1;
	while (++i < params.philo_num)
	{
		if (pthread_join(philo[i].th, NULL))
		{
			// pthread detach all ??
			free(philo);
			free(params.fork);
			return (ft_printerr(5));
		}
	}
	// releasing data and memory
	i = -1;
	while (++i < params.philo_num)
	{
		if (pthread_mutex_destroy(&params.fork[i].lock))
		{
			// pthread detach all ??
			free(philo);
			free(params.fork);
			return (ft_printerr(6)); // FREE EVERYTHING <-------------------------[!]
		}
	}
	free(philo);
	free(params.fork);
	return (0);
}
