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

/*	One master function pointed to by param used in pthread_create
	calling other functions depending on philo state
	function for each action (eating, sleeping, thinking
	called by thread function
	each printing action and philosopher ID
	then calling back ft_thread and ultimately running in a loop
	time keeping tho ??????????????
	Colors according to action or philosopher?*/


void	ft_sleep(t_philo *p)
/*passing whole struct or just status and TIMMING ?????????*/
{
	printf(GREEN);
	printf("%ld Philosopher %d is sleeping.\n", elaps_time(p->timings.init_t), p->N);
	p->state = SLEEPING;
	usleep (p->timings.sleep_time);
}
void	ft_eat(t_philo *p)
/*err handling ??
  needs releas r_fork if l_fork unnavailable (queue) */
{
	while (!p->l_fork->is_taken || !p->r_fork->is_taken) // waitting to eat; but not quite cuz priorities
	{
		if (!try_get_fork(p->r_fork))
			continue ;
		if (!try_get_fork(p->l_fork))
			release_fork(p->r_fork);
	}
	printf(BLUE);
	printf("%ld Philosopher %d is eating.\n", elaps_time(p->timings.init_t), p->N);
	p->last_meal = elaps_time(p->timings.init_t); // ??
	p->state = EATING;
	usleep (p->timings.meal_time);
	release_fork(p->l_fork);
	release_fork(p->r_fork);
}
void	ft_think(t_philo *p)
{
	printf("%ld Philosopher %d is thinking.\n", elaps_time(p->timings.init_t), p->N);
	p->state = THINKING;
	// time left ft ????????
}

void	*ft_thread(void *philo)
{
	t_philo	*p;
	// long	curr_time;

	p = (t_philo *)philo;
	p->timings.init_t = ft_gettime(); //or initialize both initial and current here???? <---------------[!]
	if (p->timings.init_t < 0)
		return (NULL);	// err handling ??? <-----------------------------------------------------------{!}
	p->last_meal = p->timings.init_t; // ??
	while (not_dead(p) /*&& !eaten_enough && nobody_died*/) // check state, num_meals (if any is given), ??check state of others(can't)
	// while (1)
	{	

		/*testing*/
		// curr_time = elaps_time(p->timings.init_t); // so I can check for NULL ret; pass to functions
		// if (!curr_time)
		// 	return (NULL);
		/*testing*/

		printf(CLR_DFT);
		// if (is_dead) //time_to_die
		// 	continue ;
		if (p->state == EATING)
			ft_sleep(p);
		else if (p->state == SLEEPING)
			ft_think(p);
		else if (p->state == THINKING)
		{
			// try_get_forks();
			ft_eat(p);
		}
	}

	return (NULL);
}
