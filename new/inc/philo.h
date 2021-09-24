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

/*------TMP------*/
# ifdef DEBUGMODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)
# endif
/*------TMP------*/

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>

typedef pthread_mutex_t t_mutex;
typedef	struct timeval t_tv;

#define USECS 100000

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define CLR_DFT "\033[0m"

/*arguments (excepting 1st)
  + initial time*/
typedef enum	e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	SOMEONE_DIED,
	FULL // ...
}	t_philo_state;

typedef struct s_timings
{
	long long	dead_time;
	long		meal_time;
	long		sleep_time;
	int			num_meals;
	long long	init_t;
}				t_timings;

typedef struct s_fork
{
	bool		is_taken;
	t_mutex		lock;
}	t_fork;

typedef struct  s_philo
{
	int				N;
	pthread_t		th;
	t_philo_state	state;
	long long		last_meal;
	int				meals_eaten;
	t_timings 		timings;
	t_fork			*r_fork;
	t_fork			*l_fork;
	t_mutex			*printlock;
	t_mutex			*deathlock;
	long long		*someone_died;
	int				*err;
	// bool			*nobody_died;
}	t_philo;

/*parameters external to t_philo (sorta)
  arg 1
  timings
  forks and mutexes [array]
  printer lock
  death time
  */
typedef struct s_params
{
	int			philo_num;
	t_timings 	timings; // any use here?
	t_fork		*fork;
	t_mutex		printlock;
	t_mutex		deathlock;
	long long	someone_died;
	int			retnum;
	// int			errnum; // for pthread errs
}	t_params;

/*main_utils.c*/
// t_philo	*init_philo(t_params *params);
t_philo	*init_structs(char **argv, t_params *params);
bool	mutex_init(t_params *params, t_philo *philo, int i);
int		free_everything(t_params *params, t_philo *philo, int i, int ret);
int		init_threads(int philo_num, t_philo *philo, int i);

/*utils.c*/
bool	ft_isdigit(int c);
int		ft_atoi(const char *str);
bool	nobody_died(t_philo *p, int N);

/*thread.c*/
void	*ft_thread(void *philo);

/*thread_utils.c*/
bool	try_get_fork(t_fork *fork);
bool	release_fork(t_fork *fork);
bool	ft_take_forks(t_philo *p);
bool	not_dead(t_philo *p);
bool	ft_printmsg(t_philo *p, char *msg);

// /*err.c*/
// int		argcheck(int argc, char **argv);
// int		ft_printerr(int n);
int		set_error(int *ptr, int err);

/*time.c*/
long long	ft_gettime(void);
long long	elaps_time(long long init_time);
void		ft_usleep(int time, t_philo *p);
// void		ft_usleep(int time);

#endif
