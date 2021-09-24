/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:36:06 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/14 19:36:08 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	not_dead(t_philo *p)
/*				  Dead			Not dead
				 ______		   __________
Someone died |    10us	 		 ret 0
			    to print
Nobody died	 | print death 		 ret 1	
*/
{
	if (p->timings.dead_time < elaps_time(p->last_meal))
	{
		p->state = DEAD;
		printf("time : %lld died A %d\n",elaps_time(p->timings.init_t),p->N);
		ft_printmsg(p, "died");
		return (0);
	}
	if (pthread_mutex_lock(p->deathlock))
		return (set_error(p->err, 8));
	if(*p->someone_died)
	{
		if (pthread_mutex_unlock(p->deathlock))
			return (set_error(p->err, 8));
		return (0);
	}
	if (pthread_mutex_unlock(p->deathlock))
		return (set_error(p->err, 8));
	return (1);
}

bool	ft_printmsg(t_philo *p, char *msg)
/*DOING TOO MUCH
  MAYBE JUST 1 LOCK*/
{
	long long	time;
	long long	time_since_death;

	time_since_death = elaps_time(*p->someone_died);
	time = elaps_time(p->timings.init_t);
	if (pthread_mutex_lock(p->printlock))
		return (set_error(p->err, 8));
	if (*p->someone_died)
	{
		if (pthread_mutex_unlock(p->printlock))
			return (set_error(p->err, 8));
		return (0);
	}
	if (!*p->someone_died && p->state == DEAD)
		*p->someone_died = ft_gettime();

/*	if (time_since_death > 10)
	{
		// printf(CLR_DFT);
		if (pthread_mutex_unlock(p->printlock))
			return (set_error(p->err, 8));
		return (0);
	}
	else if (!(*p->someone_died && p->state != DEAD))*/

	printf("%lld %d %s\n", time, p->N, msg);
	if (pthread_mutex_unlock(p->printlock))
		return (set_error(p->err, 8));
	return (1);
}

bool	try_get_fork(t_fork *f) // ERR CHECKING
{
	pthread_mutex_lock(&f->lock);
	/*if (!f->is_taken)
	{
		f->is_taken = 1;
		pthread_mutex_unlock(&f->lock);
		return (1);
	}*/
	
	// pthread_mutex_unlock(&f->lock);
	return (1);//alterado para 1 era 0
}

bool	release_fork(t_fork *f) // ERR CHECKING
{
	
	// pthread_mutex_lock(&f->lock);
	// f->is_taken = 0;
	pthread_mutex_unlock(&f->lock);
	return (0); // ...
}

bool	ft_take_forks(t_philo *p) // ERR CHECKING
{
	if (!p->l_fork)
		return (0);
	if (2 * p->timings.meal_time > elaps_time(p->last_meal))
		return (0);
	if (try_get_fork(p->r_fork))
	{
		if (try_get_fork(p->l_fork))
		{
			ft_printmsg(p, "has taken a fork");
			ft_printmsg(p, "has taken a fork");
			// release_fork(p->r_fork);
			// release_fork(p->l_fork);
			return (1);
		}
		// release_fork(p->r_fork);
	}
	return (0);
}
