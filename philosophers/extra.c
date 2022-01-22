/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkeskint <bkeskint@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:47:44 by bkeskint          #+#    #+#             */
/*   Updated: 2021/12/16 01:06:24 by bkeskint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start(t_philo *philo)
{
	int		i;
	long	tme;

	i = 0;
	tme = get_time();
	while (i < philo[i].ttl)
	{
		philo[i].timestamp = tme;
		philo[i].lstmeal = philo[i].timestamp;
		if (pthread_create(&philo[i].id, NULL, run, &philo[i]))
			return (1);
		usleep(20);
		i++;
	}
	while (i > 0)
	{
		pthread_join(philo[i - 1].id, NULL);
		i--;
	}
	return (0);
}

long	get_time(void)
{
	long			ret;
	struct timeval	tv;

	usleep(20);
	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	ret = (long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (ret);
}

void	print(t_philo *philo, char *str)
{
	if (!*philo->rip)
	{
		pthread_mutex_lock(philo->death);
		printf("%010ld", get_time() - philo->timestamp);
		printf(" %3d %s\n", philo->nbr, str);
		pthread_mutex_unlock(philo->death);
	}
}

void	clean(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo[i].death);
	pthread_mutex_destroy(philo[i].access);
	if (philo->death)
		free(philo[i].death);
	if (philo->access)
		free(philo[i].access);
	if (philo->rip)
		free(philo[i].rip);
	while (i < philo->ttl)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
	free(philo);
}

int	ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	else
		return (0);
}
