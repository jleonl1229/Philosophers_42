/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chores.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:09:10 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:09:10 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork);
	print_message("This philosopher has taken a fork", philosopher, philosopher->id);
	if (philosopher->num_of_philosophers == 1)
	{
		ft_usleep(philosopher->time_to_die);
		pthread_mutex_unlock(philosopher->right_fork);
		return ;
	}
	pthread_mutex_lock(philosopher->left_fork);
	print_message("This philosopher has taken a fork", philosopher, philosopher->id);
	philosopher->eating = 1;
	print_message("This philosopher is eating", philosopher, philosopher->id);
	pthread_mutex_lock(philosopher->eat_lock);
	philosopher->last_lunch = ft_gettime();
	philosopher->spaghettis_eaten++;
	pthread_mutex_unlock(philosopher->eat_lock);
	ft_usleep(philosopher->time_to_eat);
	philosopher->eating = 0;
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	return ;
}

void	nap(t_philosopher *philosopher)
{
	print_message("This philosopher is sleeping", philosopher, philosopher->id);
	ft_usleep(philosopher->time_to_sleep);
	return ;
}

void	think(t_philosopher *philosopher)
{
	print_message("This philosopher is thinking", philosopher, philosopher->id);
	return ;
}
