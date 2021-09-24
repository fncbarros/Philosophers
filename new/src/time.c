/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:27:47 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/06 13:27:49 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime(void)
{
	t_tv	t;

	if (gettimeofday(&t, NULL))
		return (0);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
	// return (t.tv_sec * 1000000 + t.tv_usec);
}

long long	elaps_time(long long init_time)
{
	long long	curr_time;
	int			r;

	curr_time = ft_gettime();
	r = curr_time - init_time;
	if (!init_time || !curr_time)
		return (0);
	return (r);
}

void	ft_usleep(int time, t_philo *p)
{
	long long	curr;

	curr = ft_gettime();
	while (ft_gettime() - curr <= time)
	{
		if (p->timings.dead_time < elaps_time(p->last_meal))
		{
			printf("MORTE B\n");
			p->state = DEAD;
			ft_printmsg(p, "died");
			return ;
		}
	}
}
