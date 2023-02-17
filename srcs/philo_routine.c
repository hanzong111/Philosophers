/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:17:49 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/17 13:32:39 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(int sleeptime, int eat_start, struct timeval start_time)
{
	while (1)
	{
		usleep(10);
		if ((get_time(start_time) - eat_start) >= sleeptime)
			return ;
	}
}

void	choose_fork(t_philo *philo, t_fork **left, t_fork **right)
{
	*left = philo->right;
	*right = philo->left;
}

void	eat(t_philo	*philo)
{
	t_fork	*left;
	t_fork	*right;

	choose_fork(philo, &left, &right);
	pthread_mutex_lock(&left->fork_mutex);
	get_message(philo, philo->n, "has taken left fork", GREEN);
	pthread_mutex_lock(&right->fork_mutex);
	get_message(philo, philo->n, "has taken right fork", GREEN);
	get_message(philo, philo->n, "is eating", GREEN);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->total_ate++;
	philo->last_ate = get_time(philo->main->start_time);
	pthread_mutex_unlock(&philo->philo_mutex);
	ft_sleep(philo->input->eat_time,
		get_time(philo->main->start_time), philo->main->start_time);
	pthread_mutex_unlock(&philo->left->fork_mutex);
	pthread_mutex_unlock(&philo->right->fork_mutex);
}

void	*routine(void	*philo)
{
	if ((((t_philo *)philo)->n % 2) == 0)
		ft_sleep(25, get_time(((t_philo *)philo)->main->start_time),
			((t_philo *)philo)->main->start_time);
	eat((t_philo *)philo);
	while (1)
	{
		get_message((t_philo *)philo,
			((t_philo *)philo)->n, "is sleeping", YELLOW);
		ft_sleep(((t_philo *)philo)->input->eat_time,
			get_time(((t_philo *)philo)->main->start_time),
			((t_philo *)philo)->main->start_time);
		get_message((t_philo *)philo,
			((t_philo *)philo)->n, "is thinking", BLUE);
		eat((t_philo *)philo);
	}
}
