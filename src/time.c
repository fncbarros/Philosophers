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

	curr_time = ft_gettime();
	if (!init_time || !curr_time)
		return (0);
	return (curr_time - init_time);
}

// long long	elaps_time_tv(t_tv init_time)
// {
// 	t_tv		curr_time;
// 	long long	elapsed;

// 	if (gettimeofday(&curr_time, 0))
// 		return (0);
// 	elapsed = (curr_time.tv_sec - init_time.tv_sec) * 1000000;
// 	elapsed += curr_time.tv_usec - init_time.tv_usec;
// 	return (elapsed);
// }

void	ft_usleep(int time)
{
	long long	curr;

	curr = ft_gettime();
	usleep(time - time / 30);
	while (ft_gettime() - curr <= time)
	 	continue ;
}
