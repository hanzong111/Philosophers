/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:17:49 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/05 18:35:09 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->left->fork_mutex);
	get_message(philo, philo->n, "has taken a fork");
	pthread_mutex_lock(&philo->right->fork_mutex);
	get_message(philo, philo->n, "has taken a fork");
	get_message(philo, philo->n, "is eating");
	usleep(philo->input->eat_time * 1000);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->total_ate++;
	philo->last_ate = get_time(philo->main->start_time);
	pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(&philo->left->fork_mutex);
	pthread_mutex_unlock(&philo->right->fork_mutex);
}

void	*routine(void	*philo)
{
	if ((((t_philo *)philo)->n % 2) == 0)
		usleep(2500);
	eat((t_philo *)philo);
	while (1)
	{
		get_message((t_philo *)philo, ((t_philo *)philo)->n, "is sleeping");
		usleep(((t_philo *)philo)->input->sleep_time * 1000);
		get_message((t_philo *)philo, ((t_philo *)philo)->n, "is thinking");
		eat((t_philo *)philo);
	}
}
