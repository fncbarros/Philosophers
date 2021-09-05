#include "../inc/philo.h"

/*function for each action (eating, sleeping, thinking
	called by thread function
	each printing action and philosopher ID
	then calling back ft_thread and ultimately running in a loop
	time keeping tho ??????????????
	Colors according to action or philosopher?*/

void	ft_sleep(t_philo *p)
/*passing whole struct or just status and TIMMING ?????????*/
{
	p->state = 'S';
	
	printf("\033[0;32m");
	printf("Philosopher %d is sleeping.\n\n", p->N);
	usleep (99999);
	ft_thread(p);
}
void	ft_eat(t_philo *p)
{
	p->state = 'E';
	printf("\033[0;34m");
	printf("Philosopher %d is eating.\n\n", p->N);
	usleep (99999);
	ft_thread(p);

}
void	ft_think(t_philo *p)
{
	p->state = 'T';
	printf("Philosopher %d is thinking.\n\n", p->N);
	usleep (99999);
	ft_thread(p);
}

void	*ft_thread(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;

	/*test*/
	printf("Philosopher %d in state = %c\n", p->N, p->state);
	usleep (99999);
	/*test*/
	
	printf("\033[0m");
	if (p->state == 'E')
		ft_sleep(p);
	if (p->state == 'S')
		ft_think(p);
	if (p->state == 'T')
		ft_eat(p);

	// if (p->state == 'D') //???
	return (NULL);
}