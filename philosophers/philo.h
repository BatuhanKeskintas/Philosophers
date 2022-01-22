/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkeskint <bkeskint@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:44:44 by bkeskint          #+#    #+#             */
/*   Updated: 2021/12/16 01:06:29 by bkeskint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo {
	int				nbr;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*nfork;
	pthread_mutex_t	*death;
	pthread_mutex_t	*access;
	int				ttl;
	int				ttdie;
	int				tteat;
	int				ttslp;
	int				meals;
	int				act;
	int				myfork;
	int				*yourfork;
	int				*rip;
	long			timestamp;
	long			lstmeal;
	long			lstact;
}		t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		initialize(int argc, char **argv, t_philo *philo);
int		start(t_philo *philo);
int		set(int i, int argc, char **argv, t_philo *philo);
void	print(t_philo *philo, char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*run(void *ptr);
void	clean(t_philo *philo);
long	get_time(void);
size_t	ft_strlen(const char *s);

#endif
