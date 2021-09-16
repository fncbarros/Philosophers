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

long	ft_gettime(void)
{
	t_tv	t;

	if (gettimeofday(&t, NULL))
		return (-1);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
	// return (t.tv_sec * 1000000 + t.tv_usec);
}

long	elaps_time(long init_time)
{
	long	curr_time;

	curr_time = ft_gettime();
	if (curr_time == -1)
		return (0);
	return (curr_time - init_time);
}
