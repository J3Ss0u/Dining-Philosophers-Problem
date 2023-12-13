/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:17:02 by sacharai          #+#    #+#             */
/*   Updated: 2023/12/13 03:43:59 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef struct	s_data t_data;
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct		s_philo
{
  pthread_t		thread;
  int			id;
  long			last_time;
  int			eating_counter;
  t_fork		*l_fork;
  t_fork		*r_fork;
  t_data		*data;
}	t_philo;

typedef	struct s_data
{
	int			philo_nbr;
	long		eat_time;
	long		death_time;
	long		sleep_time;
	int			limit_meals;
	long		start_philo;
	t_fork		*forks;
	t_philo		*philos;
}	t_data;



int	ft_atoi(const char *str);
int	check_args(char **av);
int parse_fill(int ac, char **av, t_data *data);

#endif