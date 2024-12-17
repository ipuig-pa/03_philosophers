/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:04:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:41:41 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_env *env)
{
	int		philo_id;
	t_philo	*philo;

	env->start_time = get_time_msec();
	if (pthread_create(&env->monitor, NULL, &monitor, env) != 0)
		return (final_free(env), 0);
	env->philo = (pthread_t *)malloc(env->num_philo * sizeof(pthread_t));
	if (!env->philo)
		return (0);
	philo_id = 1;
	while (philo_id <= env->num_philo)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (0);
		philo->id = philo_id;
		philo->env = env;
		if (pthread_create(&env->philo[philo_id - 1], \
												NULL, &routine, philo) != 0)
			return (final_free(env), 0);
		philo_id++;
	}
	return (1);
}

int	join_philo_threads(t_env *env)
{
	int	i;

	i = 0;
	if (pthread_join(env->monitor, NULL) != 0)
		return (final_free(env), 0);
	while (i < env->num_philo)
	{
		if (pthread_join(env->philo[i], NULL))
			return (final_free(env), 0);
		i++;
	}
	return (1);
}

int	initiate_mutex(t_env *env)
{
	int	i;

	env->fork = (pthread_mutex_t *) \
			malloc(env->num_philo * sizeof(pthread_mutex_t));
	if (!env->fork)
		return (0);
	i = 0;
	while (i++ < env->num_philo)
	{
		if (pthread_mutex_init(&env->fork[i - 1], NULL) != 0)
			return (final_free(env), 0);
	}
	env->last_meal_mutex = (pthread_mutex_t *) \
			malloc(env->num_philo * sizeof(pthread_mutex_t));
	if (!env->last_meal_mutex)
		return (0);
	i = 0;
	while (i++ < env->num_philo)
	{
		if (pthread_mutex_init(&env->last_meal_mutex[i - 1], NULL) != 0)
			return (final_free(env), 0);
	}
	if (pthread_mutex_init(&env->status_mutex, NULL) != 0)
		return (final_free(env), 0);
	return (1);
}

void	destroy_mutex(t_env *env)
{
	int	i;

	if (env->fork)
	{
		i = 0;
		while (i++ < env->num_philo)
			pthread_mutex_destroy(&env->fork[i - 1]);
		free(env->fork);
	}
	if (env->last_meal_mutex)
	{
		i = 0;
		while (i++ < env->num_philo)
			pthread_mutex_destroy(&env->last_meal_mutex[i - 1]);
		free(env->last_meal_mutex);
	}
	pthread_mutex_destroy(&env->status_mutex);
}
