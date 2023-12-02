/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:53:39 by sacharai          #+#    #+#             */
/*   Updated: 2023/12/02 06:42:15 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_spaces(char *str)
{
	int	j;

	j = 0;
	while (str[j + 1] && (str[j] == '\t' || str[j] == '\n' 
		|| str[j] == '\v' || str[j] == '\f' || str[j] == '\r' || str[j] == ' '))
	{
		j++;
	}
	return (j);
}

int check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = ft_spaces(av[i]);
		if (av[i][j + 1] && av[i][j] == '+')
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

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

int	main(int ac, char **av)
{
	int	philo_num;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Please provide the correct number of arguments.\n");
		return (1);
	}
	if (check_args(av) == 1)
		return (1);

	printf("Correct\n");
	philo_num = ft_atoi(av[1]);
	return (0);

}