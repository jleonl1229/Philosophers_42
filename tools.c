/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:08:03 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 15:08:03 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_print_error("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_gettime();
	while ((ft_gettime() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	ft_atoi(const char	*str)
{
	int	i;
	int	sign;
	int	num;
	int	flag;

	i = 0;
	flag = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	while ((str[i] == '+' || str[i] == '-') && flag == 0)
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
		flag = 1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	return (num * sign);
}

int	ft_print_red(char *s)
{
	return (printf("\033[0;91m%s\033[0;97m\n", s));
}

int	ft_print_error(char *s)
{
	int	i;

	i = 0;
	i += ft_print_red("Error  ");
	i += printf("%s", s);
	return (i);
}