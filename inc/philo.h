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

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef pthread_mutex_t t_fork;
typedef	struct timeval t_tv;


#define USECS 100010

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CLR_DFT "\033[0m"

typedef struct s_params
{
	int		philo_num; //nop
	int		dead_time; //ttd
	int		meal_time; //tte
	int		sleep_time; //tts
	int		num_meals;  //
	t_fork	*fork; // need array of forks
	suseconds_t	init_t;
	// t_tv	curr_t;
}   t_params;

typedef struct  s_philo
{
	int			N;
	pthread_t	th;
	char		state; //E[ating], S[leeping], T[hinking], D[ead]
	t_params	*params;
}   t_philo;

/*utils.c*/
int		ft_atoi(const char *str);

/*thread.c*/
void	*ft_thread(void *philo);

/*err.c*/

#endif
