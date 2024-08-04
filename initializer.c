/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:02 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:09:02 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_setting(t_setting *setting, t_philosopher *philosopher)
{
	setting->dead_flags = 0;
	setting->philosopher = philosopher;
	pthread_mutex_init(&setting->dead_lock, NULL);
	pthread_mutex_init(&setting->eat_lock, NULL);
	pthread_mutex_init(&setting->create_lock, NULL);
	return ;
}

void	init_forks(pthread_mutex_t *forks, int philosophers_num)
{
	int	i;

	i = 0;
	while (i < philosophers_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return ;
}

void	init_input(t_philosopher *philosopher, char **argv)
{
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	philosopher->num_of_philosophers = ft_atoi(argv[1]);
	if (argv[5])
		philosopher->count_of_spaghettis = ft_atoi(argv[5]);
	else
		philosopher->count_of_spaghettis = -1;
	return ;
}

void	init_philosophers(t_philosopher *philosopher, t_setting *setting, \
					pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		init_input(&philosopher[i], argv);
		philosopher[i].id = i + 1;
		philosopher[i].eating = 0;
		philosopher[i].spaghettis_eaten = 0;
		philosopher[i].timer = ft_gettime();
		philosopher[i].last_lunch = ft_gettime();
		philosopher[i].dead_lock = &setting->dead_lock;
		philosopher[i].eat_lock = &setting->eat_lock;
		philosopher[i].create_lock = &setting->create_lock;
		philosopher[i].dead = &setting->dead_flags;
		philosopher[i].right_fork = &forks[i];
		if (i == 0)
			philosopher[i].left_fork = &forks[philosopher[i].num_of_philosophers - 1];
		else
			philosopher[i].left_fork = &forks[i - 1];
		i++;
	}
	return ;
}