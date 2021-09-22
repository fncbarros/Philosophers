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
		if (p->l_fork->is_taken) // case philo num == 1
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
		{
			pthread_mutex_unlock(&p->r_fork->lock);
			pthread_mutex_unlock(&p->l_fork->lock);
			return ;
		}
		p->state = EATING;
		if (!ft_printmsg(p, "is eating."))
		{
			pthread_mutex_unlock(&p->r_fork->lock);
			pthread_mutex_unlock(&p->l_fork->lock);
			return ;
		}
		p->meals_eaten++;
		p->last_meal = ft_gettime();
		if (!p->last_meal)
		{
			pthread_mutex_unlock(&p->r_fork->lock);
			pthread_mutex_unlock(&p->l_fork->lock);
			set_error(p->err, 7);
			return ;
		}
		ft_usleep(p->timings.meal_time);
		p->r_fork->is_taken = 0;
		p->l_fork->is_taken = 0;
		if (!ft_printmsg(p, "has dropped both forks."))
		{
			pthread_mutex_unlock(&p->r_fork->lock);
			pthread_mutex_unlock(&p->l_fork->lock);
			return ;
		}
		if (pthread_mutex_unlock(&p->r_fork->lock) || pthread_mutex_unlock(&p->l_fork->lock))
			return ;
	}
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
	p->timings.init_t = ft_gettime();
	if (!p->timings.init_t)
	{
		set_error(p->err, 7);
		return (NULL);
	}
	p->last_meal = p->timings.init_t;
	while (not_dead(p) && !*p->someone_died)
	{
		/*starvation check*/
		if (p->timings.num_meals &&
				p->meals_eaten >= p->timings.num_meals)
			break ;
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
			ft_eat(p);
	}
	return (NULL);
}
