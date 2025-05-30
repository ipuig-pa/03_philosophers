/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:59:58 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:11:17 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		check_deaths(env);
		if (is_finished(env))
			break ;
	}
	return (arg);
}

void	check_deaths(t_env *env)
{
	int	philo_id;

	philo_id = 1;
	while (philo_id <= env->num_philo)
	{
		if (get_time_msec() - env->start_time - get_last_meal(env, philo_id) \
															> env->time_die)
		{
			die(env, philo_id);
			break ;
		}
		philo_id++;
	}
}

int	is_finished(t_env *env)
{
	int	finished;

	pthread_mutex_lock(&env->status_mutex);
	finished = (env->dead_philo > 0 || env->fed_philo == env->num_philo);
	pthread_mutex_unlock(&env->status_mutex);
	return (finished);
}

void	die(t_env *env, int philo_id)
{
	pthread_mutex_lock(&env->status_mutex);
	env->dead_philo++;
	printf("%lld %i died\n", get_time_msec() - env->start_time, philo_id);
	pthread_mutex_unlock(&env->status_mutex);
}
