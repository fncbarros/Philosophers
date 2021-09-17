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
/*Not sure if it protects anything outside function (whats the point then if no var??)*/
{
	// try ... condition to prevent waiting for mutex ??? queue?
	if (fork->is_taken)
		return (0);
	fork->is_taken = 1;
	if (pthread_mutex_lock(&fork->lock))
		return (0);
	return (1);
}

bool	release_fork(t_fork *fork)
{
	if (pthread_mutex_unlock(&fork->lock))
		return (0);
	fork->is_taken = 0;
	return (1);
}

bool	not_dead(t_philo *p) // print_or_die
/*KILL EVERYONE */
{
	// printf ("%lld\n",elaps_time(p->last_meal));
	if (p->timings.dead_time >= elaps_time(p->last_meal))
		return (1);
	else
	{
		pthread_mutex_lock(p->g_lock); // not really
		p->nobody_died = 0;
		printf(RED);
		ft_printmsg(p, "has died.");
		p->state = DEAD;
		printf(CLR_DFT);
		pthread_mutex_unlock(p->g_lock);
		exit(1);
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

void	ft_printmsg(t_philo *p, char *msg)
{
	long long	time;

	time = elaps_time(p->timings.init_t);
	pthread_mutex_lock(p->g_lock);
	printf("%lld Philosopher %d %s\n", time, p->N, msg);
	pthread_mutex_unlock(p->g_lock);
}