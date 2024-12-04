/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:55:44 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/04 16:38:13 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_env
{
	long long		start_time;
	int				num_philo;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	int				x_eat;
	int				philo_id;
	int				fed_philo;
	int				dead_philo;
	pthread_mutex_t	*fork;
	pthread_t		*philo;
}	t_env;

//threads and mutex
int			create_philo_threads(t_env *env);
void		join_philo_threads(t_env *env);
int			initiate_mutex(t_env *env);
void		destroy_mutex(t_env *env);

//routine
void		*routine(t_env *env);
long long	eat(t_env *env, int philo_id, long long last_meal);
void		sleep(t_env *env, int philo_id, long long last_meal);
void		think(t_env *env, int philo_id, long long last_meal);
void		die(t_env *env, int philo_id);

//helper
long long	get_time_msec(void);
long long	get_value(char *str);

#endif
