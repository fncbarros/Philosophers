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

// typedef pthread_mutex_t fork
// typedef pthread_t        philo

typedef struct s_params
{
    int             philo_num; //nop
    int             dead_time; //ttd
    int             meal_time; //tte
    int             sleep_time; //tts
    int             num_meals;  //
    pthread_mutex_t fork; // == number of philosophers
}   t_params;

typedef struct  s_philo
{
    int         N;
    pthread_t   th;
    char        state; //E[ating], S[leeping], T[hinking], D[ead]
    t_params    *params;
}   t_philo;

/*utils.c*/
int     ft_atoi(const char *str);

/*thread.c*/
void	*ft_thread(void *philo);

#endif
