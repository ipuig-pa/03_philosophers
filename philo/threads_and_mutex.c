/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:04:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/16 11:31:42 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_threads(t_env *env)
{
	int		philo_id;
	t_philo	*philo;

	pthread_create(&env->monitor, NULL, &monitor, env);
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
		update_last_meal(env, philo->id, env->start_time);
		pthread_create(&env->philo[philo_id - 1], NULL, &routine, philo);
		//if (!env->philo[env->philo_id - 1])
			//handle_error: free everything and exit clean
		//es considera que entren en race per agafar philo_id?!
		philo_id++;
	}
	join_philo_threads(env);
	return (1);
}

void	join_philo_threads(t_env *env)
{
	int	i;

	i = 0;
	pthread_join(env->monitor, NULL);
	while (i < env->num_philo)
	{
		pthread_join(env->philo[i], NULL);
		//no se si aqui tambe he de mantenir el check o no. que retorna el join?
		if (!env->philo[i])
			//handle_error: free everything and exit clean
		i++;
	}
}

int	initiate_mutex(t_env *env)
{
	int	i;

	env->fork = (pthread_mutex_t *)malloc(env->num_philo * sizeof(pthread_mutex_t));
	if (!env->fork)
		return (0);
	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_init(&env->fork[i], NULL);
		//no se si he de fer checking tambe aqui o no?
		i++;
	}
	env->last_meal_mutex = (pthread_mutex_t *)malloc(env->num_philo * sizeof(pthread_mutex_t));
	if (!env->last_meal_mutex)
		return (0);
	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_init(&env->last_meal_mutex[i], NULL);
		//no se si he de fer checking tambe aqui o no?
		i++;
	}
	pthread_mutex_init(&env->status_mutex, NULL);
	return (1);
}

void	destroy_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_destroy(&env->fork[i]);
		//no se si he de fer checking tambe aqui o no?
		i++;
	}
	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_destroy(&env->last_meal_mutex[i]);
		//no se si he de fer checking tambe aqui o no?
		i++;
	}
	pthread_mutex_destroy(&env->status_mutex);
}
