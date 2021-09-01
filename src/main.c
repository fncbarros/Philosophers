/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:35:25 by fbarros           #+#    #+#             */
/*   Updated: 2021/09/01 16:35:28 by fbarros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*One master function pointed to by param used in pthread_create
		calling other functions depending on philo state*/

int	callcheck(void *ptr, size_t size)
/*calloc's and err checks
    Adds NULL by default (???)*/
{ 
	ptr = calloc(1, size + 1); // '+1'..?
	if (!ptr)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_t	*philos;

	if (argc != 5 && argc != 6)
		return (1);
	if (!callcheck(&philos, sizeof(pthread_t) * ft_atoi(argv[1])))
		return (1);

	...

	free(philos);
	return (0);
}
