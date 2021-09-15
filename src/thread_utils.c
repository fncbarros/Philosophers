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
	if (pthread_mutex_lock(&fork->lock))
		return (0);
	fork->is_taken = 1;
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
/*someone died var
	ft_exit*/
{
	if ((long)p->timings.dead_time > elaps_time(p->last_meal))
		return (1);
	else
	{
		pthread_mutex_lock(p->g_lock); // not really
		p->nobody_died = 0;
		printf(RED);
		printf("%ld Philosopher %d has died.\n", elaps_time(p->timings.init_t), p->N);
		p->state = DEAD;
		pthread_mutex_unlock(p->g_lock);
		return (0);
	}
}
