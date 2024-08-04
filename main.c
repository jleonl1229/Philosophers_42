/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:08:55 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:08:55 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c > 47 && c < 58));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_digit_string(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_argument_checker(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_print_error("The argument number is not valid. 4 to 5 arguments are expected.\n"));
	if (ft_digit_string(argv[1]) \
		|| ft_atoi(argv[1]) > MAX_PHILOSOPHERS || ft_atoi(argv[1]) <= 0)
		return (ft_print_error("The maximum number of philosophers are 200.\n"));
	if (ft_digit_string(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (ft_print_error("The time of dying is not valid.\n"));
	if (ft_digit_string(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (ft_print_error("The time of eating is not valid.\n"));
	if (ft_digit_string(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (ft_print_error("The time of sleeping is not valid.\n"));
	if ((argv[5] && (ft_atoi(argv[5]) < 0)) || ft_digit_string(argv[5]))
		return (ft_print_error("The total number of the spaghetti philosophers have ate are not valid.\n"));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_setting		setting;
	t_philosopher	philosopher[MAX_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (init_argument_checker(argc, argv))
		return (EXIT_FAILURE);
	init_setting(&setting, philosopher);
	init_forks(forks, ft_atoi(argv[1]));
	init_philosophers(philosopher, &setting, forks, argv);
	thread_create(&setting, forks);
	destroy_mutex(NULL, &setting, forks);
	return (EXIT_SUCCESS);
}
