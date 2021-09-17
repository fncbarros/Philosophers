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
	p->state = SLEEPING;
	ft_printmsg(p, "is sleeping.");
	ft_usleep(p->timings.sleep_time);
	// usleep((useconds_t)p->timings.sleep_time);
}

void	ft_eat(t_philo *p)
/*if odd take right one first
	delay ?
	release first if second taken then return (for dead checking)*/
{
	// if (p->N % 2 == 0)
	// {
	if (!try_get_fork(p->r_fork))
		return ;
	if (!ft_printmsg(p, "has taken a fork."))
		return ;
		if (!try_get_fork(p->l_fork))
		{
			release_fork(p->r_fork);
			ft_printmsg(p, "has released a fork.");
			return ;
		}
	if (!ft_printmsg(p, "has taken a fork."))
		return ;
	// }
	// else
	// {
	// 	if (!try_get_fork(p->l_fork))
	// 		return ;
	// 	ft_printmsg(p, "has taken a fork.");
	// 		if (!try_get_fork(p->r_fork))
	// 		{
	// 			release_fork(p->l_fork);
	// 			return ;
	// 		}
	// 	ft_printmsg(p, "has taken a fork.");
	// }
	
	
	p->state = EATING;
	if(!ft_printmsg(p, "is eating."))
		return ;
	p->last_meal = ft_gettime(); // ??
	p->meals_eaten++;	
	ft_usleep(p->timings.meal_time);
	// usleep((useconds_t)p->timings.meal_time);
	release_fork(p->r_fork);
	release_fork(p->l_fork);
	// while (!release_fork(p->l_fork) || !release_fork(p->r_fork)) // in case it fails to unlock..?
	// 	continue ;
	ft_printmsg(p, "has released both forks.");
	pthread_mutex_unlock(&p->l_fork->lock); // hate it ... 
}

void	ft_think(t_philo *p)
{
	p->state = THINKING;
	ft_printmsg(p, "is thinking.");
	// time left ????????
}

void	*ft_thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	// while (p->timings.init_t <= 0) // retry in case of error. init_t won't be same for all threads !!
	/*TIME INIT*/ p->timings.init_t = ft_gettime(); // err check
	// p->last_meal = elaps_time(p->timings.init_t); // ??
	p->last_meal = p->timings.init_t; // ??
	while (not_dead(p) && p->nobody_died && !eaten_enough(p)) // check state, num_meals (if any is given), ??check state of others(can't)
	{
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
			ft_eat(p);
	}
	return (philo);
}
