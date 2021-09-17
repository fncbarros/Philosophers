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

#include "philo.h"

bool	try_get_fork(t_fork *fork)
/* Need condition in case there's but 1 fork
Not sure if it protects anything outside function (whats the point then if no var??)*/
{
	if (pthread_mutex_lock(&fork->lock))
		return (0);
	if (fork->is_taken)
	{
		if (pthread_mutex_unlock(&fork->lock))
			return (0);
		return (0);
	}
	fork->is_taken = 1;
	if (pthread_mutex_unlock(&fork->lock))
		return (0);
	return (1);
}

bool	release_fork(t_fork *fork)
/*l.:42 if <fork> is the 2nd to be put down 
<second_fork> will be 0 after this operation 
to avoid anybody aleggingto be taking an already holding fork*/
{
	static bool	second_fork;

	if (pthread_mutex_lock(&fork->lock))
		return (0);
	fork->is_taken = 0;
	second_fork ^= 1; 
	if (!second_fork)
		return (1);
	if (pthread_mutex_unlock(&fork->lock))
		return (0);
	return (1);
}

bool	not_dead(t_philo *p) // print_or_die
/*KILL EVERYONE */
{
	// printf ("%lld\n",elaps_time(p->last_meal));
	if (pthread_mutex_lock(p->g_lock))
		return (0);
	else if (p->timings.dead_time >= elaps_time(p->last_meal) && p->nobody_died) // they'll all print dead this way!!
	{
		if (pthread_mutex_unlock(p->g_lock))
			return (0);
		return (1);
	}
	else
	{
		p->nobody_died = 0;
		printf(RED);
		p->state = DEAD;
		if (pthread_mutex_unlock(p->g_lock))
			return (0);
		ft_printmsg(p, "has died.");
		printf(CLR_DFT);
		return (0);
	}
}

bool	eaten_enough(t_philo *p)
/*experimental, working for now*/
{
	if (p->timings.num_meals && p->meals_eaten >= p->timings.num_meals)
	{
		p->state = DEAD;
		return (1);
	}
	return (0);
}

bool	ft_printmsg(t_philo *p, char *msg)
{
	long long	time;

	time = elaps_time(p->timings.init_t);
	pthread_mutex_lock(p->g_lock);
	if (p->state != DEAD && !p->nobody_died)
	{
		pthread_mutex_unlock(p->g_lock);
		p->state = SOMEONE_DIED;
		return (0);
	}
	printf("%lld Philosopher %d %s\n", time, p->N, msg);
	pthread_mutex_unlock(p->g_lock);
	return (1);
}