/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:32 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/09 17:31:41 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	multi_spaces(char *str)
{
	int	j;

	j = 0;
	while (str[j + 1] && (str[j] == '\t' || str[j] == '\n'
			|| str[j] == '\v' || str[j] == '\f'
			|| str[j] == '\r' || str[j] == ' '))
		j++;
	return (j);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '\0')
			return (1);
		j = multi_spaces(av[i]);
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (printf("Error: Enter a valid positive integers .\n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_fill(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	if (check_args(av))
		return (free(data), 1);
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (free(data),
				printf("Error: %s is greater than INT_MAX.\n", av[i]));
		i++;
	}
	data->philo_nbr = ft_atoi(av[1]);
	if (data->philo_nbr == 0)
		return (free(data), 1);
	data->death_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->limit_meals = ft_atoi(av[5]);
	else
		data->limit_meals = -1;
	pthread_mutex_init(&data->print_lock, NULL);
	return (0);
}

unsigned long	get_ctime(t_data *data)
{
	return (get_time() - data->start_time);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
	return (0);
}
