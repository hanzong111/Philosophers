/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_death.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:03:11 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/19 13:08:26 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	check_total_ate(t_philo *philo, int i, int *temp)
{
	if (philo->input->arg_5)
	{
		pthread_mutex_lock(&philo[i].philo_mutex);
		if (philo[i].total_ate >= philo->input->eat_max)
			*temp += 1;
		pthread_mutex_unlock(&philo[i].philo_mutex);
	}
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
			check_total_ate(philo, i, &temp);
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
