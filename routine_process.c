/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:08:22 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:08:22 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philosopher *philosopher, int id)
{
	size_t	time;

	pthread_mutex_lock(philosopher->create_lock);
	time = ft_gettime() - philosopher->timer;
	if (!dead_loop(philosopher))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philosopher->create_lock);
	return ;
}

int	philosopher_dead(t_philosopher *philosopher, size_t time_to_die)
{
	pthread_mutex_lock(philosopher->eat_lock);
	if (ft_gettime() - philosopher->last_lunch >= time_to_die
		&& philosopher->eating == 0)
		return (pthread_mutex_unlock(philosopher->eat_lock), 1);
	pthread_mutex_unlock(philosopher->eat_lock);
	return (EXIT_SUCCESS);
}

int	dead_flag(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher[0].num_of_philosophers)
	{
		if (philosopher_dead(&philosopher[i], philosopher[i].time_to_die))
		{
			print_message("has died", &philosopher[i], philosopher[i].id);
			pthread_mutex_lock(philosopher[0].dead_lock);
			*philosopher->dead = 1;
			pthread_mutex_unlock(philosopher[0].dead_lock);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	no_more_meals_flag(t_philosopher *philosopher)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philosopher[0].count_of_spaghettis == -1)
		return (0);
	while (i < philosopher[0].num_of_philosophers)
	{
		pthread_mutex_lock(philosopher[i].eat_lock);
		if (philosopher[i].spaghettis_eaten >= philosopher[i].count_of_spaghettis)
			finished_eating++;
		pthread_mutex_unlock(philosopher[i].eat_lock);
		i++;
	}
	if (finished_eating == philosopher[0].num_of_philosophers)
	{
		pthread_mutex_lock(philosopher[0].dead_lock);
		*philosopher->dead = 1;
		pthread_mutex_unlock(philosopher[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*track_routine(void *pointer)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)pointer;
	while (1)
		if (dead_flag(philosopher) == 1 || no_more_meals_flag(philosopher) == 1)
			break ;
	return (pointer);
}