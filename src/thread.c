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

#include "../inc/philo.h"

void	ft_sleep(t_philo *p)
/*passing whole struct or just status and TIMMING ?????????*/
{
	p->state = SLEEPING;
	if (!ft_printmsg(p, "is sleeping."))
		return ;
	ft_usleep(p->timings.sleep_time);
	// usleep((useconds_t)p->timings.sleep_time);
}

void	ft_eat(t_philo *p)
/*if odd take right one first
	release first if second taken then return (for dead checking)*/
{
	if (!p->r_fork->is_taken && !p->l_fork->is_taken)
	{
		pthread_mutex_lock(&p->r_fork->lock);
		p->r_fork->is_taken = 1;
		if (!ft_printmsg(p, "has grabbed a fork."))
		{
			pthread_mutex_unlock(&p->r_fork->lock);
			pthread_mutex_unlock(&p->l_fork->lock);
			return ;
		}
		if (p->l_fork->is_taken) // case philo nume == 1
		{
			p->r_fork->is_taken = 0;
			ft_printmsg(p, "has dropped a fork.");
			pthread_mutex_unlock(&p->r_fork->lock);
			pthread_mutex_unlock(&p->l_fork->lock);
			return ;
		}
		pthread_mutex_lock(&p->l_fork->lock);
		p->l_fork->is_taken = 1;
		if (!ft_printmsg(p, "has grabbed a fork."))
			return ;
		p->state = EATING;
		if (!ft_printmsg(p, "is eating."))
			return ;
		ft_usleep(p->timings.meal_time);
		p->r_fork->is_taken = 0;
		p->l_fork->is_taken = 0;
		if (!ft_printmsg(p, "has dropped both forks."))
			return ;
		if (pthread_mutex_unlock(&p->r_fork->lock) || pthread_mutex_unlock(&p->l_fork->lock))
			return ;
		p->meals_eaten++;
	}
}

void	ft_think(t_philo *p)
{
	p->state = THINKING;
	if (!ft_printmsg(p, "is thinking."))
		return ;
	// time left ????????
}

void	*ft_thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	/*TIME INIT*/ p->timings.init_t = ft_gettime(); // err check
	if (!p->timings.init_t)
		return (philo); // errnum element in t_philo ?
	// while (p->timings.init_t <= 0) // retry in case of error.
	p->last_meal = p->timings.init_t; // ??

	while (not_dead(p) && !p->someone_died && !eaten_enough(p))
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
