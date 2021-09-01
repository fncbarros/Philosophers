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

typedef struct s_params
{/*
    int number_of_philosophers; //nop
    int time_to_die; //ttd
    int time_to_eat; //tte
    int time_to_sleep; //tts
    int eat_time_num;  //         */ 
}   t_params;


typedef struct  s_philo
{
    /* pthread_t    *N
    char    state; //E(ating), S(leeping), T(hinking), D[ead]

    */ 

}   t_philo;

/*utils.c*/
int ft_atoi(const char *str);

#endif
