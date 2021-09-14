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

bool	try_get_fork(t_fork *fork)
/*Not sure if it protects anything outside function (whats the point then if no var??)*/
{

	// try ... condition to prevent waitting for mutex ???
	if (fork->is_taken)
		return (0);
	if (pthread_mutex_lock(&fork->lock)) // err handling ...! call err function, set flag?
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

bool	not_dead(t_philo *p)
{
	if ((long)p->timings.dead_time > elaps_time(p->last_meal))
		return (1);
	else
	{
		printf(RED);
		printf("Philosopher %d has died\n", p->N);
		p->state = DEAD;
		exit (1); // REMOVE <--------------------------------[!]
		return (0);
	}
}
