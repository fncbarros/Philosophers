/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:28:12 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/06 13:28:14 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(int c)
{
	if (58 > c && 47 < c)
		return (1);
	else
		return (0);
}

long long	ft_atoll(const char *str)
{
	long long	n;
	int			j;
	int			neg;

	if (!str)
		return (0);
	neg = 1;
	j = 0;
	n = 0;
	while (32 == str[j] || (8 < str[j] && 14 > str[j]))
		j++;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			neg = -1;
		j++;
	}
	while (ft_isdigit(str[j]) && str[j])
	{
		n *= 10;
		n += str[j++] - '0';
	}
	n *= neg;
	return (n);
}

bool	nobody_died(t_philo *p, int N)
{
	int	i;

	i = -1;
	while (++i < N)
	{
		if (p[i].state == DEAD)
			return (0);
	}
	return (1);
}
