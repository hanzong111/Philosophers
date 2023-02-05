/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:29:14 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/05 18:29:57 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	fork_init(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->input.total_philo)
	{
		if (pthread_mutex_init(&info->fork[i].fork_mutex, NULL) != 0)
			return (1);
		info->fork[i].n = i + 1;
	}
	return (0);
}

int	philo_init(t_info *info)
{
	int			i;
	pthread_t	temp;

	i = -1;
	while (++i < info->input.total_philo)
	{
		info->philo[i].last_ate = 0;
		info->philo[i].left = &(info->fork[i]);
		info->philo[i].right = &(info->fork[(i + 1) % info->input.total_philo]);
		info->philo[i].n = i + 1;
		info->philo[i].total_ate = 0;
		info->philo[i].input = &(info->input);
		info->philo[i].main = &(info->main);
		if (pthread_mutex_init(&(info->philo[i].philo_mutex), NULL))
			return (1);
		if (pthread_create(&temp, NULL, routine, &(info->philo[i])) != 0)
			return (1);
		pthread_detach(temp);
	}
	return (0);
}
