/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkeskint <bkeskint@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 22:43:56 by bkeskint          #+#    #+#             */
/*   Updated: 2021/12/16 00:31:39 by bkeskint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set(int i, int argc, char **argv, t_philo *philo)
{
	philo[i].nbr = i + 1;
	philo[i].ttl = ft_atoi(argv[1]);
	philo[i].ttdie = ft_atoi(argv[2]);
	philo[i].tteat = ft_atoi(argv[3]);
	philo[i].ttslp = ft_atoi(argv[4]);
	if (argc == 6)
		philo[i].meals = ft_atoi(argv[5]);
	else
		philo[i].meals = -1;
	i++;
	return (i);
}

int	numbers_handler(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (0);
	if (ft_atoi(argv[2]) < 60)
		return (0);
	if (ft_atoi(argv[3]) < 60)
		return (0);
	if (ft_atoi(argv[4]) < 60)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (0);
	return (1);
}

int	cmd_handler(int argc, char **argv)
{
	char	*str;
	int		i;

	if ((argc < 5) || (argc > 6))
		return (0);
	i = 2;
	while (i <= argc)
	{
		str = argv[i - 1];
		if (ft_strlen(str) > 10)
			return (0);
		while (*str)
		{
			if (*str != '-' && *str != '+' && !ft_isdigit(*str))
				return (0);
			str++;
		}
		i++;
	}
	return (numbers_handler(argc, argv));
}

int	error(char *s, t_philo *philo)
{
	printf("Error; %s \n", s);
	if (philo)
		clean(philo);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		err;

	err = 0;
	philo = NULL;
	if (!cmd_handler(argc, argv))
		err = error("parameters: [1-200][>=60][>=60][>=60]{>=1}",
				philo);
	if (!err)
		philo = calloc(ft_atoi(argv[1]), sizeof(t_philo));
	if (!err && !philo)
		err = error("memory allocation", philo);
	if (!err && initialize(argc, argv, philo))
		err = error("mutex creation", philo);
	if (!err && start(philo))
		err = error("memory allocation", philo);
	if (philo)
		clean(philo);
	if (err)
		return (EXIT_FAILURE);
	return (0);
}
