/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:55:44 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/16 11:42:45 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_env
{
	long long		start_time;
	int				num_philo;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	int				x_eat;
	pthread_mutex_t	status_mutex;
	int				fed_philo;
	int				dead_philo;
	pthread_mutex_t	*last_meal_mutex;
	long long		*last_meal;
	pthread_mutex_t	*fork;
	pthread_t		monitor;
	pthread_t		*philo;
}	t_env;

typedef struct s_philo
{
	int		id;
	t_env	*env;
}	t_philo;


//threads and mutex
int			create_philo_threads(t_env *env);
void		join_philo_threads(t_env *env);
int			initiate_mutex(t_env *env);
void		destroy_mutex(t_env *env);

//routine
void		*routine(void *arg);
void		eating(t_env *env, int philo_id);
void		sleeping(t_env *env, int philo_id);
void		thinking(t_env *env, int philo_id, long long time);
void		die(t_env *env, int philo_id);
int			is_finished(t_env *env);
void		increase_fed_philo(t_env *env);
void		update_last_meal(t_env *env, int philo_id, long long time);
long long	get_last_meal(t_env *env, int philo_id);

//monitor
void		*monitor(void *arg);
void		check_deaths(t_env *env);

//helper
long long	get_time_msec(void);
long long	get_value(char *str);
int			ft_msleep(long long time);

#endif
