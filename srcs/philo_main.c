/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:17:49 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/05 15:31:00 by ojing-ha         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_info	info;

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
	return (0);
}
