/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:21:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:49:29 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	leaks(void)
// {
// 	system("leaks philo");
// } atexit(leaks);

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 5 || argc > 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	memset(&env, 0, sizeof(t_env));
	init_env(&env, argc, argv);
	if (env.num_philo == -1 || env.time_die == -1 || env.time_eat == -1 \
	|| env.time_sleep == -1 || env.x_eat == -1)
		return (write(2, "Arguments must be positive integers\n", 36), 1);
	env.last_meal = (int *)malloc(env.num_philo * sizeof(int));
	if (!env.last_meal)
		return (write(2, "Malloc fail\n", 12), 1);
	memset(env.last_meal, 0, env.num_philo * sizeof(int));
	if (!initiate_mutex(&env))
		return (final_free(&env), 1);
	if (!create_philo_threads(&env))
		return (final_free(&env), 1);
	if (!join_philo_threads(&env))
		return (final_free(&env), 1);
	final_free(&env);
	return (0);
}
