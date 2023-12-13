/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:32 by sacharai          #+#    #+#             */
/*   Updated: 2023/12/13 03:58:16 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int multi_spaces(char *str)
{
	int	j;

	j = 0;
	while (str[j + 1] && (str[j] == '\t' || str[j] == '\n' 
		|| str[j] == '\v' || str[j] == '\f' || str[j] == '\r' || str[j] == ' '))
		j++;
	return (j);
}

int check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = multi_spaces(av[i]);
		if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: Invalid input. Please enter a valid positive integers .\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


int parse_fill(int ac, char **av, t_data *data)
{
	int i;
	int parsed_value;

	i = 1;
	parsed_value = 0;
	if (check_args(av))
		return (1);
	while (i < ac)
	{
		parsed_value = ft_atoi(av[i]);
		if (parsed_value == -1)
			return (printf("Error: the value %s is greater than INT_MAX.\n", av[i]));
		i++;
	}
	data->philo_nbr = ft_atoi(av[1]);
	data->death_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->limit_meals = ft_atoi(av[5]);
	else
		data->limit_meals = -1;
	return (0);
}

// __uint64_t	get_time(void)
// {
// 	struct timeval	tv;
	
// 	if (gettimeofday(&tv, NULL))
// 		return (error("gettimeofday() FAILURE\n", NULL));
// 	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000));
// }