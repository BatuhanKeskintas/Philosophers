/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkeskint <bkeskint@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:55:42 by bkeskint          #+#    #+#             */
/*   Updated: 2021/12/16 01:07:33 by bkeskint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eat(t_philo *philo)
{
	if (!philo->act && philo->myfork == 0 && *philo->yourfork == 0)
	{
		pthread_mutex_lock(&philo->fork);
		philo->myfork = philo->nbr;
		pthread_mutex_unlock(&philo->fork);
		print(philo, "has taken a fork");
		pthread_mutex_lock(philo->nfork);
		*philo->yourfork = philo->nbr;
		pthread_mutex_unlock(philo->nfork);
		print(philo, "has taken a fork");
		print(philo, "is eating");
		philo->lstact = get_time();
		philo->lstmeal = philo->lstact;
		philo->act = 1;
	}
}

void	eat_sleep(t_philo *philo)
{
	if (philo->act == 1 && get_time() - philo->lstact >= philo->tteat)
	{
		pthread_mutex_lock(&philo->fork);
		philo->myfork = 0;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_lock(philo->nfork);
		*philo->yourfork = 0;
		pthread_mutex_unlock(philo->nfork);
		if (philo->meals > 0)
			philo->meals--;
		print(philo, "is sleeping");
		philo->act = 2;
		philo->lstact = get_time();
	}
}

void	sleep_think(t_philo *philo)
{
	if (philo->act == 2 && get_time() - philo->lstact >= philo->ttslp)
	{
		print(philo, "is thinking");
		philo->act = 0;
		philo->lstact = get_time();
	}
}

int	check_death(t_philo *philo)
{
	long	ttime;

	if (*philo->rip)
		return (1);
	ttime = get_time() - philo->lstmeal;
	if (!*philo->rip && ttime > philo->ttdie)
	{
		pthread_mutex_lock(philo->access);
		*philo->rip = 1;
		pthread_mutex_lock(philo->death);
		printf("%010ld", get_time() - philo->timestamp);
		printf(" %3d died\n", philo->nbr);
		pthread_mutex_unlock(philo->death);
		usleep(50);
		return (1);
	}
	return (0);
}

void	*run(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)(ptr);
	while (philo->meals != 0 && !check_death(philo))
	{
		pthread_mutex_unlock(philo->access);
		start_eat(philo);
		eat_sleep(philo);
		sleep_think(philo);
		if (philo->meals == 0)
		{
			pthread_mutex_lock(philo->death);
			printf("%010ld", get_time() - philo->timestamp);
			printf(" \033[0;33m%3d had all meals\x1b[0m\n", philo->nbr);
			pthread_mutex_unlock(philo->death);
		}
		usleep(50);
	}
	return (NULL);
}
