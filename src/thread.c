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
	t_tv	tv;

	p->state = 'S';
	gettimeofday(&tv, NULL);
	printf(GREEN);
	printf("%d Philosopher %d is sleeping.\n", tv.tv_usec - p->params->init_t, p->N);
	usleep (USECS);
	ft_thread(p);
}
void	ft_eat(t_philo *p)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	p->state = 'E';
	printf(BLUE);
	printf("%d Philosopher %d is eating.\n", tv.tv_usec - p->params->init_t, p->N);
	usleep (USECS);
	ft_thread(p);

}
void	ft_think(t_philo *p)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	p->state = 'T';
	printf("%d Philosopher %d is thinking.\n", tv.tv_usec - p->params->init_t, p->N);
	usleep (USECS);
	ft_thread(p);
}

void	*ft_thread(void *philo)
{
	t_philo	*p;
	static bool	kickstart;

	p = (t_philo *)philo;
	printf(CLR_DFT);
	

	//time init
	if (!kickstart)
	{
		t_tv	time;
		if (gettimeofday(&time, NULL))
			return (NULL);
		p->params->init_t = time.tv_usec;
		kickstart = 1;
	}
	

	if (p->state == 'E')
		ft_sleep(p);
	if (p->state == 'S')
		ft_think(p);
	if (p->state == 'T')
		ft_eat(p);

	// if (p->state == 'D') //???
	return (NULL);
}
