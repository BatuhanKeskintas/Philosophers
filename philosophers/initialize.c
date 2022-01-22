/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkeskint <bkeskint@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:53:06 by bkeskint          #+#    #+#             */
/*   Updated: 2021/12/16 00:32:29 by bkeskint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*ptr;

	ptr = calloc(1, sizeof(pthread_mutex_t));
	if ((!ptr) || (pthread_mutex_init(ptr, NULL)))
		return (NULL);
	return (ptr);
}

void	set_ptrs(t_philo *philo, int i, int j)
{
	philo[i].nfork = &philo[j - 1].fork;
	philo[i].yourfork = &philo[j - 1].myfork;
	if (!i && philo[i].ttl == 1)
		philo[i].myfork = -1;
}

int	initialize(int argc, char **argv, t_philo *philo)
{
	pthread_mutex_t	*death;
	pthread_mutex_t	*access;
	int				*rip;
	int				i;

	i = 0;
	death = init_mutex();
	access = init_mutex();
	rip = calloc(1, sizeof(int));
	if (!rip || !death || !access)
		return (1);
	while (i < ft_atoi(argv[1]))
	{
		if (i)
			set_ptrs(philo, i, i);
		if (pthread_mutex_init(&philo[i].fork, NULL))
			return (1);
		philo[i].death = death;
		philo[i].access = access;
		philo[i].rip = rip;
		i = set(i, argc, argv, philo);
	}
	set_ptrs(philo, 0, i);
	return (0);
}
