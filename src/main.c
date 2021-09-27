/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:35:16 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/01 16:35:18 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "ft_error.h"

int	main(int argc, char **argv)
/*l.26: EARLY ERROR CHECKING
  l.29: INITIALIZING ARGUMENTS
  l.34: CREATING MUTEXES
  l.36: CREATING THREADS*/
{
	t_philo		*philo;
	t_params	params;
	int			ret;

	philo = NULL;
	ret = 0;
	if (!argcheck(argc, argv))
		return (ft_printerr(1));
	philo = init_structs(argv, &params);
	if (!philo)
		return (ft_printerr(2));
	if (!mutex_init(&params, philo, -1))
		return (ft_printerr(3));
	ret = init_threads(params.philo_num, philo, -1);
	if (!ret)
		ret = params.retnum;
	return (ft_printerr(free_everything(&params, philo, -1, ret)));
}
