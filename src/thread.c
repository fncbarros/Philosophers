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
	if (!ft_printmsg(p, "is sleeping"))
		return ;
	release_fork(p->r_fork, p->err);
	release_fork(p->l_fork, p->err);
	p->state = SLEEPING;
	ft_usleep(p->timings.sleep_time, p);
}

void	ft_eat(t_philo *p)
{
	if (ft_take_forks(p))
	{
		p->state = EATING;
		if (!ft_printmsg(p, "is eating"))
			return ;
		p->meals_eaten++;
		p->last_meal = ft_gettime();
		ft_usleep(p->timings.meal_time, p);
	}
}

void	ft_think(t_philo *p)
{
	p->state = THINKING;
	ft_printmsg(p, "is thinking");
	ft_usleep(10, p);
}

void	*ft_thread(void *philo)
{
	t_philo				*p;

	p = (t_philo *)philo;
	while (not_dead(p) && !*p->err)
	{
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
		{
			if (p->timings.num_meals
				&& p->meals_eaten >= p->timings.num_meals)
				break ;
			ft_eat(p);
		}
	}
	return (NULL);
}
