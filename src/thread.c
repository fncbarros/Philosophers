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

/*function for each action (eating, sleeping, thinking
	called by thread function
	each printing action and philosopher ID
	then calling back ft_thread and ultimately running in a loop
	time keeping tho ??????????????
	Colors according to action or philosopher?*/

void	ft_sleep(t_philo *p)
/*passing whole struct or just status and TIMMING ?????????*/
{
	p->state = 'S';
	printf(GREEN);
	printf(/*%d Philosopher*/" %d is sleeping.\n", /*tv.tv_usec - p->params->init_t,*/ p->N);
	usleep (USECS);
}
void	ft_eat(t_philo *p)
{
	p->state = EATING;
	printf(BLUE);
	printf(/*%d Philosopher*/" %d is eating.\n", /*tv.tv_usec - p->params->init_t,*/ p->N);
	usleep (USECS);
}
void	ft_think(t_philo *p)
{
	p->state = 'T';
	printf(/*%d Philosopher*/" %d is thinking.\n", /*tv.tv_usec - p->params->init_t,*/ p->N);
	usleep (USECS);
}

void	*ft_thread(void *philo)
{
	t_philo	*p;
	t_tv	curr_time;

	p = (t_philo *)philo;
	printf(CLR_DFT);
	
	if (gettimeofday(&curr_time, NULL))
		return (NULL);
	p->params->init_t = curr_time.tv_usec;	
	while (is_not_dead && !eaten_enough && nobody_died)
	{
		if (gettimeofday(&curr_time, NULL))
			return (NULL);
		if (is_dead)
			continue ;
		if (p->state == EATING)
			ft_sleep(p);
		if (p->state == SLEEPING)
			ft_think(p);
		if (p->state == THINKING)
			ft_eat(p);
	}
	return (NULL);
}
