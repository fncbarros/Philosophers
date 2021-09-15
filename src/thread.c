/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:27:57 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/06 13:28:00 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	One master function pointed to by param used in pthread_create
	calling other functions depending on philo state
	function for each action (eating, sleeping, thinking
	called by thread function
	each printing action and philosopher ID
	then calling back ft_thread and ultimately running in a loop
	time keeping tho ??????????????
	Colors according to action or philosopher?*/

void	ft_sleep(t_philo *p)
/*passing whole struct or just status and TIMMING ?????????*/
{
	printf("%ld Philosopher %d is sleeping.\n", elaps_time(p->timings.init_t), p->N);
	p->state = SLEEPING;
	usleep (p->timings.sleep_time);
}

void	ft_eat(t_philo *p)
{
	if (!try_get_fork(p->r_fork)) // try get forks (plural)
		return ;
	printf("%ld Philosopher %d has taken a fork.\n", elaps_time(p->timings.init_t), p->N);
		if (!try_get_fork(p->l_fork))
		{
			release_fork(p->r_fork); // !!!!!!
			return ;
		}
	printf("%ld Philosopher %d has taken a fork.\n", elaps_time(p->timings.init_t), p->N);
	printf("%ld Philosopher %d is eating.\n", elaps_time(p->timings.init_t), p->N);
	p->last_meal = elaps_time(p->timings.init_t); // ??
	p->state = EATING;
	usleep (p->timings.meal_time);
	while (!release_fork(p->l_fork) || !release_fork(p->r_fork)) // in case it fails to unlock
		continue ;
	printf("%ld Philosopher %d has realeased both forks\n", elaps_time(p->timings.init_t), p->N);
}

void	ft_think(t_philo *p)
{
	printf("%ld Philosopher %d is thinking.\n", elaps_time(p->timings.init_t), p->N);
	p->state = THINKING;
	// time left ????????
}

void	*ft_thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	// p->timings.init_t = 0;
	// while (p->timings.init_t <= 0) // retry in case of error. init_t won't be same for all threads !!
	// 	p->timings.init_t = ft_gettime();
	p->last_meal = p->timings.init_t; // ??
	while (not_dead(p) && p->nobody_died/*&& !eaten_enough && nobody_died*/) // check state, num_meals (if any is given), ??check state of others(can't)
	{
		// printf(CLR_DFT);
		// if (is_dead) //time_to_die
		// 	continue ;
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
		{
			//if (try_get_forks()); // returns even if failed
				ft_eat(p);
		}
	}
	return (philo);
}
