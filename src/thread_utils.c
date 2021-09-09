#include "../inc/philo.h"

void	try_get_fork(t_fork *fork)
/*void for now*/
{
	if (!pthread_mutex_lock(&fork->lock)) // err handling ...! call err function, set flag?
		return (-1);
	fork->is_taken = 1;
	return (1);
}
