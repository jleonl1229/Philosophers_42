/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:08:13 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:08:13 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(char *str, t_setting *setting, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&setting->create_lock);
	pthread_mutex_destroy(&setting->eat_lock);
	pthread_mutex_destroy(&setting->dead_lock);
	while (i < setting->philosopher[0].num_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	return ;
}

int	dead_loop(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->dead_lock);
	if (*philosopher->dead == 1)
		return (pthread_mutex_unlock(philosopher->dead_lock), 1);
	pthread_mutex_unlock(philosopher->dead_lock);
	return (0);
}

void	*philosopher_routine(void *pointer)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)pointer;
	if (philosopher->id % 2 == 0)
		ft_usleep(philosopher->time_to_eat - 20);
	while (!dead_loop(philosopher))
	{
		eat(philosopher);
		nap(philosopher);
		think(philosopher);
	}
	return (pointer);
}

int	thread_create(t_setting *setting, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	track;

	if (pthread_create(&track, NULL, &track_routine, setting->philosopher) != 0)
		destroy_mutex("Thread creation error", setting, forks);
	i = 0;
	while (i < setting->philosopher[0].num_of_philosophers)
	{
		if (pthread_create(&setting->philosopher[i].thread, NULL, &philosopher_routine,
				&setting->philosopher[i]) != 0)
			destroy_mutex("Thread creation error", setting, forks);
		i++;
	}
	i = 0;
	if (pthread_join(track, NULL) != 0)
		destroy_mutex("Thread join error", setting, forks);
	while (i < setting->philosopher[0].num_of_philosophers)
	{
		if (pthread_join(setting->philosopher[i].thread, NULL) != 0)
			destroy_mutex("Thread join error", setting, forks);
		i++;
	}
	return (EXIT_SUCCESS);
}