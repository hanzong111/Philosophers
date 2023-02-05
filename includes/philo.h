/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:50:46 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/02/05 15:22:32 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				n;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_input
{
	int				total_philo;
	int				eat_time;
	int				sleep_time;
	int				death_time;
	int				eat_max;
}	t_input;

typedef struct s_main
{
	struct timeval	start_time;
	pthread_mutex_t	write_mutex;
}	t_main;

typedef struct s_philo
{
	int				n;
	int				total_ate;
	int				last_ate;
	pthread_mutex_t	philo_mutex;
	t_fork			*left;
	t_fork			*right;
	t_input			*input;
	t_main			*main;
}	t_philo;

typedef struct s_info
{

	t_input			input;
	t_main			main;
	t_fork			fork[200];
	t_philo			philo[200];
}	t_info;

//libft
long			ft_atoi(const char *str);
int				str_is_digit(char *str);

//getters
void			get_inputs(int argc, char **argv, t_info *info);
struct timeval	get_current_time(void *timezone);
int				get_time(struct timeval start);
void			get_message(t_philo *philo, int i, char *str);

//inits
int				fork_init(t_info *info);

#endif