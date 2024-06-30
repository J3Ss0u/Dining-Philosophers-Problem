/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:24:50 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:45 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	message(*philo, "is eating");
	philo->eating_counter++;
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->data->last_eat_lock);
	philo->last_time = get_ctime(philo->data);
	pthread_mutex_unlock(&philo->data->last_eat_lock);
	if (philo->data->limit_meals != -1
		&& philo->eating_counter == philo->data->limit_meals)
	{
		pthread_mutex_lock(&philo->data->eat_counter_lock);
		philo->data->nbr_philos_meal++;
		pthread_mutex_unlock(&philo->data->eat_counter_lock);
	}
}

void	philo_sleep(t_philo *philo)
{
	message(*philo, "is sleeping");
	ft_usleep(philo->data->sleep_time);
}

void	philo_think(t_philo *philo)
{
	message(*philo, "is thinking");
}

void	*routine(void *thread)
{
	t_philo			*philo;
	pthread_mutex_t	*next_fork;

	philo = thread;
	if (philo->id % 2)
		ft_usleep(philo->data->eat_time);
	while (1)
	{
		next_fork = &philo->data->philos[(philo->id + 1)
			% philo->data->philo_nbr].fork;
		pthread_mutex_lock(&philo->fork);
		message(*philo, "has taken a fork");
		pthread_mutex_lock(next_fork);
		message(*philo, "has taken a fork");
		philo_eat(philo);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(next_fork);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	message(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.data->print_lock);
	printf("%lu %d %s\n", get_ctime(philo.data), philo.id + 1, str);
	pthread_mutex_unlock(&philo.data->print_lock);
}
