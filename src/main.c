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
	int			i;
	t_params	params;
	// pthread_t	*philo;

	if (argc != 5 && argc != 6)
		return (1);
	params.philo_num = ft_atoi(argv[1]);


	//allocating memory
	philo = (t_philo *)malloc((sizeof(t_philo) * params.philo_num) + 1); // probly no need for NULL term since there's philo_num
	if (!philo)
		return (2);
	// if (!callcheck(&philo, sizeof(t_philo) * params.philo_num))
	// 	return (1);


	// initializing arguments
	params.dead_time = ft_atoi(argv[2]);
	params.meal_time = ft_atoi(argv[3]);
	params.sleep_time = ft_atoi(argv[4]);
	params.num_meals = ft_atoi(argv[5]);


	//creating threads
	i = 0;
	while (i < params.philo_num) // not sure if it won't just execute sequentially
	{
		philo[i].N = i + 1;
		/*test*/
		philo[i].state = 'T';
		/*test*/
		philo[i].params = &params;
		if (pthread_create(&philo[i].th, NULL, &ft_thread, &philo[i]))	//technically passing single t_philo struct to function (hopefully)
			return (3);
		if (pthread_join(philo[i].th, NULL))
			return (3);
		i++;
	}
	printf("ÖUT!\n");
	// (philo + i) = NULL;

	free(philo);
	return (0);
}
