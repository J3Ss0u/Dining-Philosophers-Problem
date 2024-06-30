/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:53:39 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/09 19:32:16 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_safe_last_eat(t_philo p)
{
	unsigned long	l;

	pthread_mutex_lock(&p.data->last_eat_lock);
	l = p.last_time;
	pthread_mutex_unlock(&p.data->last_eat_lock);
	return (l);
}

int	get_safe_all_philo_eaten(t_data *d)
{
	int	f;

	pthread_mutex_lock(&d->eat_counter_lock);
	f = d->nbr_philos_meal - d->philo_nbr;
	pthread_mutex_unlock(&d->eat_counter_lock);
	return (f);
}

void	check_philos(t_data *d)
{
	int	i;

	i = 0;
	while (1)
	{
		if (get_ctime(d) - get_safe_last_eat(d->philos[i]) >= d->death_time)
		{
			message(d->philos[i], "died");
			pthread_mutex_lock(&d->print_lock);
			return ;
		}
		if (d->limit_meals != -1 && !get_safe_all_philo_eaten(d))
		{
			pthread_mutex_lock(&d->print_lock);
			return ;
		}
		i %= d->philo_nbr;
		usleep(100);
	}
}

void	finish(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
		pthread_mutex_destroy(&data->philos[i++].fork);
	pthread_mutex_destroy(&data->eat_counter_lock);
	pthread_mutex_destroy(&data->last_eat_lock);
	pthread_mutex_destroy(&data->print_lock);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Please provide the correct number of arguments.\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (parse_fill(ac, av, data))
		return (1);
	if (data->limit_meals == 0)
		return (free(data), 1);
	philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!philos)
		return (1);
	if (data_init(philos, data))
		return (1);
	check_philos(data);
	finish(data);
	return (0);
}
