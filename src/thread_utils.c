#include "../inc/philo.h"

int	try_get_fork(t_fork *fork)
/*void for now*/
{

	// try ... condition to prevent waitting for mutex ???

	if (pthread_mutex_lock(&fork->lock)) // err handling ...! call err function, set flag?
		return (0);
	fork->is_taken = 1;
	return (1);
}

int	release_fork(t_fork *fork)
{
	if (pthread_mutex_unlock(&fork->lock))
		return (0);
	fork->is_taken = 0;
	return (1);
}