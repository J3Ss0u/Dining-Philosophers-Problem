/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 05:17:02 by sacharai          #+#    #+#             */
/*   Updated: 2024/01/09 19:33:35 by sacharai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	unsigned long		last_time;
	int					eating_counter;
	pthread_mutex_t		fork;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					philo_nbr;
	unsigned long		eat_time;
	unsigned long		death_time;
	unsigned long		sleep_time;
	int					limit_meals;
	long				start_philo;
	pthread_mutex_t		eat_counter_lock;
	pthread_mutex_t		last_eat_lock;
	unsigned long		start_time;
	pthread_mutex_t		print_lock;
	int					nbr_philos_meal;
	t_philo				*philos;
}	t_data;

int				ft_atoi(const char *str);
int				check_args(char **av);
int				parse_fill(int ac, char **av, t_data *data);
int				data_init(t_philo *philo, t_data *data);
int				ft_usleep(unsigned long time);
void			*routine(void *thread);
void			message(t_philo philo, char *str);
unsigned long	get_time(void);
unsigned long	get_ctime(t_data *data);

#endif