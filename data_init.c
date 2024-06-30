/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:22:15 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/09 18:57:21 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	philo_init(t_philo *philo, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo[i].id = i;
		philo[i].data = data;
		philo[i].eating_counter = 0;
		philo[i].last_time = 0;
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
}

int	data_init(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	data->philos = philos;
	data->start_time = get_time();
	data->nbr_philos_meal = 0;
	pthread_mutex_init(&data->last_eat_lock, NULL);
	pthread_mutex_init(&data->eat_counter_lock, NULL);
	philo_init(philos, data);
	while (i < data->philo_nbr)
	{
		if (pthread_create(&philos[i].thread,
				NULL, routine, (void *)&philos[i]))
			return (1);
		if (pthread_detach(philos[i].thread))
			return (1);
		i++;
	}
	return (0);
}
