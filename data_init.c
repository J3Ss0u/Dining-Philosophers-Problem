/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:22:15 by sacharai          #+#    #+#             */
/*   Updated: 2023/12/16 22:22:48 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->forks[i].fork_id = i;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
}

void	get_forks(t_philo *philo, int philo_p)
{
	int	max_nbr;

	max_nbr = philo->data->philo_nbr;
	philo->l_fork = &philo->data->forks[(philo_p + 1) % 5]; // possiple problem
	philo->r_fork = &philo->data->forks[philo_p];
}

void	philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->eating_counter = 0;
		philo->flag = 0;
		philo->data = data;
		
		get_forks(philo, i);
	}
	
}

int	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if(!data->philos)
		return (1);
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if(!data->forks)
		return (1);
	fork_init(data);
	philo_init(data);
	
	return (0);
}