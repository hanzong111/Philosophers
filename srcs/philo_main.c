/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 00:17:49 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/19 13:04:14 by ojing-ha         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_info	info;

	info.status = 1;
	if (error_checks(argc, argv) != 0)
		return (1);
	get_inputs(argc, argv, &info);
	if (pthread_mutex_init(&info.main.write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info.main.switch_mutex, NULL) != 0)
		return (1);
	info.main.counter = 1;
	if (fork_init(&info) != 0)
		return (1);
	info.main.start_time = get_current_time(NULL);
	if (philo_init(&info) != 0)
		return (1);
	return (check_philo(info.philo));
}
