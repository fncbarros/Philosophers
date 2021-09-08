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

typedef pthread_mutex_t t_mutex;
typedef	struct timeval t_tv;


#define USECS 100010

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CLR_DFT "\033[0m"

// QUEUE for waiting time <-------------

/*arguments (excepting 1st)*/
typedef struct s_timings
{
	int		dead_time; //ttd
	int		meal_time; //tte
	int		sleep_time; //tts
	int		num_meals;  //
}				t_timings;

typedef struct s_fork
{
	bool		fork;
	t_mutex		lock;
}	t_fork;


/*parameters external to t_philo (sorta);
  arg 1
  timings
  forks and mutexes [array]
  initial time
  */
typedef struct s_params
{
	int			philo_num;
	t_timings 	timings;
	t_fork		*mutex;
	suseconds_t	init_t;
}   t_params;

typedef enum	e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_philo_state;

typedef struct  s_philo
{
	int				N;
	pthread_t		th;
	t_philo_state	state;
	t_params		*params; // maybe not use this and pass struct holding both t_pilo and s_params ??? No
	t_timings 		timings;
	bool			*r_fork;	// N0 can take fork 0 and 1, N1 can take 1 and 2 ... Nphil_num can take fork phil_num and 0 (r_fork being equivalent to corresponding N)
	bool			*l_fork;
}   t_philo;

/*utils.c*/
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

/*thread.c*/
void	*ft_thread(void *philo);

/*err.c*/
int	argcheck(int argc, char **argv);

#endif
