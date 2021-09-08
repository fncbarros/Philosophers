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

int	callcheck(void *ptr, size_t size)
/*calloc's and err checks(...to save a line[...would save 2 if I could use exit().....])
  NOT IN USE ATM*/
{ 
	ptr = calloc(1, size + 1); // '+1'..?
	if (!ptr)
		return (0);
	return (1);
}

int	init_structs(char **argv, t_philo **philo, t_params *params, int i)
/* change to t_philo	*init_structs(char **argv, t_params *params, int i) <---------------------------[CHANGE!!!!]



	UPDATE LINE NUMS
	l.39-43: initializing arguments
  l.44-45: allocating memory for arrays
  l.50: copying value of t_timings(args) to each philosopher struct(presumably)
  l.51-55: Attributing each philosopher a fork throught pointers (rightmost fork being 0 and leftmost being philo_num - 1)
  */
{
	params->philo_num = ft_atoi(argv[1]);
	params->timings.dead_time = ft_atoi(argv[2]);
	params->timings.meal_time = ft_atoi(argv[3]);
	params->timings.sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		params->timings.num_meals = ft_atoi(argv[5]);
	else
		params->timings.num_meals = -1;	
	*philo = malloc((sizeof(t_philo) * params->philo_num ));
	params->mutex = malloc(sizeof(t_fork) * params->philo_num);
	if (!philo || !params->mutex)
		return (0);
	while (++i < params->philo_num)
	{
		philo[i]->N = i + 1;
		philo[i]->params = params;
		philo[i]->timings = params->timings;
		philo[i]->r_fork = &params->mutex[i].fork;
		philo[i]->l_fork = &params->mutex[i + 1].fork;
	}
	philo[i - 1]->l_fork = &params->mutex[0].fork;
	return (1);
}

int	main(int argc, char **argv)
/*Initialize array of t_philo struct
  Initialize t_params struct*/
{
	t_philo		*philo;
	t_params	params;
	int			i;


	philo = NULL;
	i = -1;



	// early err checking
	if (!argcheck(argc, argv)) //not working
		return (1);
	// initializing arguments
	if (!init_structs(argv, &philo, &params, i)) // passing 5th arg or not, i for saving lines
		return (2);



	// creating mutexes
	while (++i < params.philo_num)
	{
		if (pthread_mutex_init(&params.mutex[i].lock, NULL))
			return (3);
	}
	//creating threads
	i = -1;
	while (++i < params.philo_num)
	{
		philo->state = THINKING;
		// philo[i].params = &params;
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


	// releasing data and memory
	i = -1;
	while (++i < params.philo_num)
		pthread_mutex_destroy(&params.mutex[i].lock);
	free(philo);
	free(params.mutex);
	
	return (0);
}
