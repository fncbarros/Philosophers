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

/*One master function pointed to by param used in pthread_create
		calling other functions depending on philo state*/

int	callcheck(void *ptr, size_t size)
/*calloc's and err checks
    Adds NULL by default (???)*/
{ 
	ptr = calloc(1, size + 1); // '+1'..?
	if (!ptr)
		return (0);
	return (1);
}

int	init_structs(char **argv, t_philo **philo, t_params *params)
{
	params->philo_num = ft_atoi(argv[1]);
	params->timings.dead_time = ft_atoi(argv[2]);
	params->timings.meal_time = ft_atoi(argv[3]);
	params->timings.sleep_time = ft_atoi(argv[4]);
	params->timings.num_meals = ft_atoi(argv[5]);

	// if (!callcheck(&params->fork, sizeof(bool) * params->philo_num))
	// 	return (0);
	// if (!callcheck(&params->mutex, sizeof(t_fork) * params->philo_num))
	// 	return (0);
	// if (!callcheck(&philo, sizeof(t_philo) * params->philo_num))
	// 	return (0);
	
	*philo = malloc((sizeof(t_philo) * params->philo_num)/* + 1*/);
	if (!philo)
		return (0);
	params->fork = malloc(sizeof(bool) * params->philo_num);
	if (!params->fork)
		return (0);
	params->lock = malloc(sizeof(t_mutex) * params->philo_num);
	if (!params->lock)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_params	params;
	int			i;


	philo = NULL;
	i = -1;


	// (void)argc;
	// early err checking
	if (!argcheck(argc, argv)) //not working
		return (1);
	// initializing arguments
	if (!init_structs(argv, &philo, &params))
		return (2);

	// creating mutexes
	while (++i < params.philo_num)
	{
		if (pthread_mutex_init(&params.lock[i], NULL))
			return (3);
	}
	//creating threads
	i = -1;
	while (++i < params.philo_num)
	{
		philo[i].N = i + 1;

		/*test*/
		philo[i].state = THINKING;
		/*test*/

		philo[i].params = &params;
		if (pthread_create(&philo[i].th, NULL, &ft_thread, &philo[i]))
			return (4);
	}
	i = -1;
	while (++i < params.philo_num)
	{
		if (pthread_join(philo[i].th, NULL))
			return (5);
	}



	// (philo + i) = NULL;

	free(philo);
	free(params.lock);
	free(params.fork);
	return (0);
}
