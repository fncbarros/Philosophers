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

void	ft_sleep(t_philo *p)
/*passing whole struct or just status and TIMMING ?????????*/
{
	printf("%ld Philosopher %d is sleeping.\n", elaps_time(p->timings.init_t), p->N);
	p->state = SLEEPING;
	usleep (p->timings.sleep_time);
}








void	ft_eat(t_philo *p)
/*if odd take right one first
	delay ?
	release first if second taken then return (for dead checking)*/
{
	if (p->N % 2 == 0)
	{
		if (!try_get_fork(p->r_fork))
			return ;
		printf("%ld Philosopher %d has taken a fork.\n", elaps_time(p->timings.init_t), p->N);
			if (!try_get_fork(p->l_fork))
			{
				release_fork(p->r_fork);
				printf("%ld Philosopher %d has released a fork.\n", elaps_time(p->timings.init_t), p->N);
				return ;
			}
		printf("%ld Philosopher %d has taken a fork.\n", elaps_time(p->timings.init_t), p->N);
	}
	else
	{
		if (!try_get_fork(p->l_fork))
			return ;
		printf("%ld Philosopher %d has taken a fork.\n", elaps_time(p->timings.init_t), p->N);
			if (!try_get_fork(p->r_fork))
			{
				release_fork(p->l_fork);
				return ;
			}
		printf("%ld Philosopher %d has taken a fork.\n", elaps_time(p->timings.init_t), p->N);
	}
	
	
	
	printf("%ld Philosopher %d is eating.\n", elaps_time(p->timings.init_t), p->N);
	p->last_meal = elaps_time(p->timings.init_t); // ??
	p->state = EATING;
	p->meals_eaten++;
	usleep (p->timings.meal_time);
	while (!release_fork(p->l_fork) || !release_fork(p->r_fork)) // in case it fails to unlock..?
		continue ;
	printf("%ld Philosopher %d has stopped eating\n", elaps_time(p->timings.init_t), p->N);
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
	// while (p->timings.init_t <= 0) // retry in case of error. init_t won't be same for all threads !!
		// p->timings.init_t = ft_gettime();
	p->last_meal = p->timings.init_t; // ??
	while (not_dead(p) && p->nobody_died && !eaten_enough(p)) // check state, num_meals (if any is given), ??check state of others(can't)
	{
		// if (is_dead) //time_to_die
		// 	continue ;
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
			ft_eat(p);
	}
	return (philo);
}
