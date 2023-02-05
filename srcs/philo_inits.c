/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:29:14 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/05 14:21:01 by ojing-ha         ###   ########.fr       */
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
