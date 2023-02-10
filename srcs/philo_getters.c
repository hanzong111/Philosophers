/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:22:09 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/10 14:19:43 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_inputs(int argc, char **argv, t_info *info)
{
	info->input.total_philo = ft_atoi(argv[1]);
	info->input.death_time = ft_atoi(argv[2]);
	info->input.eat_time = ft_atoi(argv[3]);
	info->input.sleep_time = ft_atoi(argv[4]);
	info->input.arg_5 = 0;
	if (argc == 6)
	{
		info->input.eat_max = ft_atoi(argv[5]);
		info->input.arg_5 = 1;
	}
}

struct timeval	get_current_time(void *timezone)
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

void	get_message(t_philo *philo, int i, char *str, char *color)
{	
	pthread_mutex_lock(&philo->main->write_mutex);
	if (*(philo->status))
	{
		printf("%s%d\t %d %s%s\n", color, get_time(philo->main->start_time),
		i, str, DEF);
	}
	pthread_mutex_unlock(&philo->main->write_mutex);
}
