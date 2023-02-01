/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:17:49 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/01 23:21:05 by ojing-ha         ###   ########.fr       */
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

void	*routine(t_philo *philo)
{

}

int	philo_init(t_info *info)
{
	int			i;
	pthread_t	temp;

	i = -1;
	while (++i < info->total_philo)
	{
		info->philo[i].last_ate = info->start_time;
		info->philo[i].left = &(info->fork[i]);
		info->philo[i].right = &(info->fork[(i + 1) % info->total_philo]);
		info->philo[i].n = i + 1;
		if (pthread_mutex_init(&(info->philo[i].philo_mutex), NULL))
			return (1);
		if (pthread_create(&temp, NULL, routine, &(info->philo[i])) != 0)
			return (1);
		pthread_detach(temp);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (error_checks(argc, argv) != 0)
		return (1);
	get_inputs(argc, argv, &info);
	if (pthread_mutex_init(&info.write_mutex, NULL) != 0)
		return (1);
	info.start_time = get_start_time(NULL);
	if (fork_init(&info) != 0)
		return (1);
	// if (philo_init(&info) != 0)
	// 	return (1);
	return (0);
}
