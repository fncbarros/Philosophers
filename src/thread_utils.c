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
to avoid any philosopher from claiming to be taking an already holding fork*/
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



















bool	not_dead(t_philo *p)
/*KILL EVERYONE
				Dead		Not dead
Someone died    10us	 	ret 0
			  to print
Nobody died	 print death 	ret 1	*/
{
	if (p->timings.dead_time < elaps_time(p->last_meal))
	{
		if (pthread_mutex_lock(p->deathlock))
			return (set_error(p->err, 8));
		if (!*p->someone_died)
			*p->someone_died = ft_gettime();
		p->state = DEAD;
		if (pthread_mutex_unlock(p->deathlock))
			return (set_error(p->err, 8));
		printf(RED);
		ft_printmsg(p, "has died.");
		return (0);
	}
	return (1);
}

















bool	ft_printmsg(t_philo *p, char *msg)
{
	long long	time;
	long long	time_since_death;

	time_since_death = elaps_time(*p->someone_died);
	time = elaps_time(p->timings.init_t);

	// /*------------------>DEBUG<------------------*/
	// if (p->state == DEAD)
	// {
	// 	printf("\ncurrent: %lld death_time: %lld\n", ft_gettime(), *p->someone_died);
	// 	printf("N%d time_since death = %lld time = %lld\n\n", p->N, time_since_death, time);
	// }
	// /*------------------->DEBUG<-----------------*/

	pthread_mutex_lock(p->printlock);
	if (*p->someone_died)
	{
		if (p->state == DEAD && time_since_death <= 10 && time_since_death > 0)
			printf("%lld Philosopher %d %s\n",
					*p->someone_died + time_since_death, p->N, msg);
		p->state = DEAD;
		pthread_mutex_unlock(p->printlock);
		printf(CLR_DFT);
		return (0);
	}
	printf("%lld Philosopher %d %s\n", time, p->N, msg);
	pthread_mutex_unlock(p->printlock);
	printf(CLR_DFT);
	return (1);
}
