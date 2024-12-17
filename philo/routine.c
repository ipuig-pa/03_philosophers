/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:11:35 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//THINKING TIME! que es considera que han de fer si no hi ha temps de pensar. Escriure i no ft_msleep o be no escriure-ho?
//no se si hauria de retornar alguna cosa amb mes sentit?
void	*routine(void *arg)
{
	int			x_feed;
	t_env		*env;
	int			philo_id;
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo_id = (int)philo->id;
	env = (t_env *)philo->env;
	x_feed = 0;
	if (philo_id % 2 == 0)
		thinking(env, philo_id, env->time_eat);
	else if (philo_id == env->num_philo && philo_id != 1)
		thinking(env, philo_id, 2 * env->time_eat);
	while (!is_finished(env))
	{
		eating(env, philo_id);
		if (++x_feed == env->x_eat)
			increase_fed_philo(env);
		sleeping(env, philo_id);
		thinking(env, philo_id, (float) 0.9 * (env->time_die - env->time_eat - env->time_sleep));
	}
	free(philo);
	return (arg);
}

//print when it has taken just one or both forks??
//cal que uns agafin primer els de la dreta i els altres els de l-esquerra?
void	eating(t_env *env, int philo_id)
{
	int	current_meal;

	pthread_mutex_lock(&env->fork[philo_id - 1]);
	if (!is_finished(env))
		printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
	if (env->num_philo == 1)
	{
		pthread_mutex_unlock(&env->fork[philo_id - 1]);
		ft_msleep(env->time_die);
		die(env, philo_id);
		return ;
	}
	pthread_mutex_lock(&env->fork[philo_id % env->num_philo]);
	if (!is_finished(env))
		printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
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

void	sleeping(t_env *env, int philo_id)
{
	if (!is_finished(env))
	{
		printf("%lld %i is sleeping\n", get_time_msec() - env->start_time, philo_id);
		ft_msleep(env->time_sleep);
	}
}

void	thinking(t_env *env, int philo_id, int time)
{
	if (!is_finished(env) && time >= 0)
	{
		printf("%lld %i is thinking\n", get_time_msec() - env->start_time, philo_id);
		ft_msleep(time);
	}
}

