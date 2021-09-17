
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:35:16 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/01 16:35:18 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_params	params;
	int			i;

	philo = NULL;
	i = -1;

	/*-------------TMP--------------*/
	DEBUG(printf("Debug mode on\n");)
	/*-------------TMP--------------*/

	// early err checking
	if (!argcheck(argc, argv)) //not working
		return (ft_printerr(1));
	// initializing arguments
	philo = init_structs(argv, &params); // i for saving lines
	if (!philo)
		return (ft_printerr(2));
	// creating mutexes
	if (!mutex_init(&params, philo, i))
		return (ft_printerr(3));
	// creating threads
	while (++i < params.philo_num)
	{
		/*----TMP-----*/
		// usleep(100);
		/*----TMP----*/
		params.timings.init_t = ft_gettime();
		philo[i].timings.init_t = params.timings.init_t; // the fair way
		if (pthread_create(&philo[i].th, NULL, &ft_thread, &philo[i]))
		{
			free(philo);
			free(params.fork);
			return (ft_printerr(4));
		}
	}

	/*-------------------------------TEST--------------------------------*/
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
	/*-------------------------------TEST--------------------------------*/

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
	return (free_everything(&params, philo, -1));
}
