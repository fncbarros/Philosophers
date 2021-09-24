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
	// if (elaps_time(p->last_meal) + p->timings.sleep_time > p->timings.dead_time)
	// {
	// 	release_fork(p->r_fork);
	// 	release_fork(p->l_fork);
	// 	return ;
	// }
	p->state = SLEEPING;
	ft_printmsg(p, "is sleeping");
	// ft_printmsg(p, "is sleeping");
	ft_usleep(p->timings.sleep_time, p);
}

void	ft_eat(t_philo *p)
/*if odd take right one first
	release first if second taken then return (for dead checking)

	if (2 * meal_time > curr - last_meal)
		no lock

	lock the whole thing?
	ERROR HANDLING*/
{
	//testes
	// long long temp =  ft_gettime();//ft_gettime();
	//endtestes
	if (ft_take_forks(p))
	{
		p->state = EATING;
		p->meals_eaten++;
		ft_printmsg(p, "is eating");
		p->last_meal = ft_gettime();
		// p->last_meal = temp;
		ft_usleep(p->timings.meal_time, p);
		release_fork(p->r_fork);
		release_fork(p->l_fork);
	}
}

void	ft_think(t_philo *p)
{
	p->state = THINKING;
	ft_printmsg(p, "is thinking");
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
	while (not_dead(p) && !*p->someone_died /*&& !*p->err*/)
	{
		//usleep(10);
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
		{
			if (p->timings.num_meals
				&& p->meals_eaten >= p->timings.num_meals)
				{
					// printf("FINAL NUM OF MEALS %d\n", p->meals_eaten);
					break ;
				}
			
			ft_eat(p);
		}
	}
	return (NULL);
}
