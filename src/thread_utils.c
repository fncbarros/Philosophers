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
		ft_printmsg(p, "died");
		return (0);
	}
	if (pthread_mutex_lock(p->deathlock))
		return (set_error(p->err, 8));
	if (*p->someone_died)
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
{
	long long	time;

	time = elaps_time(p->timings.init_t);
	if (time > 0)
		time--;
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
	printf("%lld %d %s\n", time, p->N, msg);
	if (pthread_mutex_unlock(p->printlock))
		return (set_error(p->err, 8));
	return (1);
}

bool	try_get_fork(t_fork *f, int *err)
/*MISSING ERROR CHECKING*/
{
	if (pthread_mutex_lock(&f->lock))
		return (set_error(err, 8));
	if (!f->is_taken)
	{
		f->is_taken = 1;
		if (pthread_mutex_unlock(&f->lock))
			return (set_error(err, 8));
		return (1);
	}
	if (pthread_mutex_unlock(&f->lock))
		return (set_error(err, 8));
	return (0);
}

bool	release_fork(t_fork *f, int *err)
/*Error checking*/
{
	if (pthread_mutex_lock(&f->lock))
		return (set_error(err, 8));
	f->is_taken = 0;
	if (pthread_mutex_unlock(&f->lock))
		return (set_error(err, 8));
	return (0);
}

bool	ft_take_forks(t_philo *p)
{
	if (!p->l_fork)
		return (0);
	if (try_get_fork(p->r_fork, p->err))
	{
		if (try_get_fork(p->l_fork, p->err))
		{
			if (!ft_printmsg(p, "has taken a fork"))
				return (0);
			if (!ft_printmsg(p, "has taken a fork"))
				return (0);
			return (1);
		}
		release_fork(p->r_fork, p->err);
	}
	return (0);
}
