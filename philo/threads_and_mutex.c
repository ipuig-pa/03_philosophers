/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:04:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/04 16:33:45 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

int	create_philo_threads(t_env *env)
{
	env->philo = (pthread_t *)malloc(env->num_philo * sizeof(pthread_t));
	if (!env->philo)
		return (0);
	env->philo_id = 1;
	while (env->philo_id <= env->num_philo)
	{
		pthread_create(&env->philo[i], NULL, &routine, env);
		if (!env->philo[i])
			//handle_error: free everything and exit clean
		env->philo_id++;
		usleep(50);
	}
	return (1);
}

void	join_philo_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philo)
	{
		pthread_join(env->philo[i], NULL);
		//no se si aqui tambe he de mantenir el check o no. que retorna el join?
		if (!env->philo[i])
			//handle_error: free everything and exit clean
		i++;
	}
	//return (pthread_create(&philo, NULL, &routine, env));
}

int	initiate_mutex(t_env *env)
{
	int	i;

	env->fork = (pthread_mutex_t *)malloc(env->num_philo * sizeof(pthread_t));
	if (!env->fork)
		return (0);
	i = 0;
	while (i < env->num_philo)
	{
		pthread_mutex_init(&env->fork[i], NULL);
		//no se si he de fer checking tambe aqui o no?
		if (!env->fork[i])
			//handle_error: free everything and exit clean
		i++;
	}
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
		if (!env->fork[i])
			//handle_error: free everything and exit clean
		i++;
	}
	return (philo);
}
