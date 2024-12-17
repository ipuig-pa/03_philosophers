/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:39:28 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int			x_feed;
	t_philo		*philo;

	philo = (t_philo *)arg;
	x_feed = 0;
	if (philo->env->num_philo == 1)
		eating_alone(philo);
	else if (philo->id % 2 == 0)
		thinking(philo, philo->env->time_eat);
	else if (philo->id == philo->env->num_philo)
		thinking(philo, 2 * philo->env->time_eat);
	while (!is_finished(philo->env))
	{
		eating(philo);
		if (++x_feed == philo->env->x_eat)
			increase_fed_philo(philo->env);
		sleeping(philo);
		thinking(philo, (float) 0.9 * (philo->env->time_die - \
						philo->env->time_eat - philo->env->time_sleep));
	}
	free(philo);
	return (arg);
}

void	eating_alone(t_philo *philo)
{
	t_env	*env;
	int		philo_id;

	philo_id = philo->id;
	env = philo->env;
	pthread_mutex_lock(&env->fork[philo_id - 1]);
	printf("%lld %i has taken a fork\n", \
			get_time_msec() - env->start_time, philo_id);
	pthread_mutex_unlock(&env->fork[philo_id - 1]);
	thinking(philo, env->time_die);
	die(env, philo_id);
}

void	eating(t_philo *philo)
{
	int		current_meal;
	t_env	*env;
	int		philo_id;

	philo_id = philo->id;
	env = philo->env;
	pthread_mutex_lock(&env->fork[philo_id - 1]);
	if (!is_finished(env))
		printf("%lld %i has taken a fork\n", \
				get_time_msec() - env->start_time, philo_id);
	pthread_mutex_lock(&env->fork[philo_id % env->num_philo]);
	if (!is_finished(env))
		printf("%lld %i has taken a fork\n", \
				get_time_msec() - env->start_time, philo_id);
	current_meal = get_time_msec() - env->start_time;
	update_last_meal(env, philo_id, current_meal);
	if (!is_finished(env))
	{
		printf("%u %i is eating\n", current_meal, philo_id);
		ft_msleep(env->time_eat);
	}
	pthread_mutex_unlock(&env->fork[philo_id - 1]);
	pthread_mutex_unlock(&env->fork[philo_id % env->num_philo]);
}

void	sleeping(t_philo *philo)
{
	t_env	*env;
	int		philo_id;

	philo_id = philo->id;
	env = philo->env;
	if (!is_finished(env))
	{
		printf("%lld %i is sleeping\n", \
					get_time_msec() - env->start_time, philo_id);
		ft_msleep(env->time_sleep);
	}
}

void	thinking(t_philo *philo, int time)
{
	t_env	*env;
	int		philo_id;

	philo_id = philo->id;
	env = philo->env;
	if (!is_finished(env) && time >= 0)
	{
		printf("%lld %i is thinking\n", \
					get_time_msec() - env->start_time, philo_id);
		ft_msleep(time);
	}
}
