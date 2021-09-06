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

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_params	params;
	int			i;

	if (argc != 5 && argc != 6)
		return (1);

	// initializing arguments
	params.philo_num = ft_atoi(argv[1]);
	params.dead_time = ft_atoi(argv[2]);
	params.meal_time = ft_atoi(argv[3]);
	params.sleep_time = ft_atoi(argv[4]);
	params.num_meals = ft_atoi(argv[5]);


	//allocating memory
	/*probly no need for NULL term since there's philo_num
		Considering allocating for an array of threads instead but that requires identifying the thread calling the functions*/
	philo = (t_philo *)malloc((sizeof(t_philo) * params.philo_num)/* + 1*/);
	if (!philo)
		return (2);
	params.fork = (t_fork *)malloc(sizeof(t_fork) * params.philo_num);
	if (!params.fork)
		return (2);
	// if (!callcheck(&params.fork, sizeof(t_fork) * params.philo_num))
	// 	return (2);
	// if (!callcheck(&philo, sizeof(t_philo) * params.philo_num))
	// 	return (2);

	//creating threads and mutexes
	i = -1;
	while (++i < params.philo_num) // not sure if it won't just execute sequentially
	{
		philo[i].N = i + 1;

		/*test*/
		philo[i].state = 'T';
		/*test*/

		philo[i].params = &params;
		if (pthread_create(&philo[i].th, NULL, &ft_thread, &philo[i]))	//technically passing single t_philo struct to function (hopefully)
			return (3);
		// if (pthread_mutex_init(&params.fork[i], NULL))
		// 	return (5);
	}
	i = -1;
	while (++i < params.philo_num)
	{
		if (pthread_join(philo[i].th, NULL))
			return (4);
	}
	
	/*debugging*/
	printf("ÖUT!\n");
	/*debugging*/

	// (philo + i) = NULL;

	free(philo);
	free (params.fork);
	return (0);
}
