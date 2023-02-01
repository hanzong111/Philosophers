/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:22:09 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/01 22:45:50 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_inputs(int argc, char **argv, t_info *info)
{
	info->total_philo = ft_atoi(argv[1]);
	info->death_time = ft_atoi(argv[2]);
	info->eat_max = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->eat_max = ft_atoi(argv[5]);
}

struct timeval	get_start_time(void *timezone)
{
	struct timeval	time;

	gettimeofday(&time, timezone);
	return (time);
}

int	get_time(struct timeval start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (((current.tv_sec - start.tv_sec) * 1000)
		+ ((current.tv_usec - start.tv_usec) / 1000));
}

void	get_message(t_info *info, int i, char *str)
{
	pthread_mutex_lock(&info->write_mutex);
	printf("%d\t %d %s\n", get_time(info->start_time),
		i, str);
	pthread_mutex_unlock(&info->write_mutex);
}
