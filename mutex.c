/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:48:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/04 15:37:36 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

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