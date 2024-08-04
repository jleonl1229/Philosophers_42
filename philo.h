/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:08:31 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:08:31 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define MAX_PHILOSOPHERS 200

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_philosopher
{
    pthread_t       thread;
    int             id;
    int             count_of_spaghettis;
    int             num_of_philosophers;
    int             *dead;
    int             spaghettis_eaten;
    int             eating;
    size_t          time_to_die;
    size_t          time_to_eat;
    size_t          time_to_sleep;
    size_t          last_lunch;
    size_t          timer; 
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *create_lock;
    pthread_mutex_t *eat_lock;
    pthread_mutex_t *dead_lock;
}               t_philosopher;

typedef struct s_setting
{
    int              dead_flags;
    pthread_mutex_t  dead_lock;
    pthread_mutex_t  eat_lock;
    pthread_mutex_t  create_lock;
    t_philosopher    *philosopher;
}                    t_setting;    

// initialize
void	init_setting(t_setting *setting, t_philosopher *philosopher);
void	init_forks(pthread_mutex_t *forks, int philos_num);
void	init_philosophers(t_philosopher *philosopher, t_setting *setting, \
					pthread_mutex_t *forks, char **argv);
void	init_input(t_philosopher *philosopher, char **argv);

// tasks
int		dead_loop(t_philosopher *philosopher);
void	*philosopher_routine(void *pointer);
int		thread_create(t_setting *setting, pthread_mutex_t *forks);
void	destroy_mutex(char *str, t_setting *generator, pthread_mutex_t *forks);

// chores
void	print_message(char *str, t_philosopher *philosopher, int id);
void	eat(t_philosopher *philosopher);
void	nap(t_philosopher *philosopher);
void	think(t_philosopher *philosopher);

// routine-process
void	*track_routine(void *pointer);
int		no_more_meals_flag(t_philosopher *philosopher);
int		dead_flag(t_philosopher *philosopher);
int		philosopher_dead(t_philosopher *philosopher, size_t time_to_die);

// tools
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int     ft_print_red(char *s);
int		ft_print_error(char *s);
int		ft_atoi(const char	*str);
int		ft_usleep(size_t milliseconds);
size_t	ft_gettime(void);

#endif