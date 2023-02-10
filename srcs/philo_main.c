/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:17:49 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/10 14:21:07 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_checks(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "Error: Invalid number of input\n", 31));
	while (++i < argc)
	{
		if (str_is_digit(argv[i]) == 0)
			return (write(2, "Error: Input must only be numbers\n", 34));
		if (ft_atoi(argv[i]) <= 0)
			return (write(2, "Error: Input number must be bigger than 1\n", 42));
	}
	return (0);
}

int	check_death(t_philo	*philo)
{
	int	current;

	current = get_time(philo->main->start_time);
	pthread_mutex_lock(&philo->philo_mutex);
	if ((current - philo->last_ate) >= philo->input->death_time)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_mutex);
	return (0);
}

int	check_philo(t_philo *philo)
{
	int	i;
	int	temp;

	while (1)
	{
		i = -1;
		temp = 0;
		while (++i < philo->input->total_philo)
		{
			if (philo->input->arg_5)
			{
				pthread_mutex_lock(&philo[i].philo_mutex);
				if (philo[i].total_ate >= philo->input->eat_max)
					temp++;
				pthread_mutex_unlock(&philo[i].philo_mutex);
			}
			if (check_death(&philo[i]))
			{
				get_message(philo, i + 1, "has died", RED);
				pthread_mutex_lock(&philo->main->write_mutex);
				*(philo->status) = 0;
				pthread_mutex_unlock(&philo->main->write_mutex);
				return (0);
			}
		}
		if (temp == philo->input->total_philo)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.status = 1;
	if (error_checks(argc, argv) != 0)
		return (1);
	get_inputs(argc, argv, &info);
	if (pthread_mutex_init(&info.main.write_mutex, NULL) != 0)
		return (1);
	info.main.start_time = get_current_time(NULL);
	if (fork_init(&info) != 0)
		return (1);
	if (philo_init(&info) != 0)
		return (1);
	return (check_philo(info.philo));
}
