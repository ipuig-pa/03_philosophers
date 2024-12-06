/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:21:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/06 17:51:09 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc < 5 || argc > 6)
		return (write(2, "Incorrect number of arguments\n", 31), 1);
	memset(&env, 0, sizeof(t_env));
	env.num_philo = (int)get_value(argv[1]);
	env.time_die = get_value(argv[2]);
	env.time_eat = get_value(argv[3]);
	env.time_sleep = get_value(argv[4]);
	if (argc == 6)
		env.x_eat = (int)get_value(argv[5]);
	if (env.num_philo == -1 || env.time_die == -1 || env.time_eat == -1 \
	|| env.time_sleep == -1 || env.x_eat == -1)
		return (write(2, "Incorrect argument format\n", 26), 1);
	env.start_time = get_time_msec();
	env.last_meal = (long long *)malloc(env.num_philo * sizeof(long long));
	if (!env.last_meal)
		return (1);
	initiate_mutex(&env);
	//fer els checks que toquin
	//if (!initiate_mutex(&env))
		//exit clean and return (1);
	create_philo_threads(&env);
	//if (!create_philo_threads(&env))
		//exit clean and return (1);
	join_philo_threads(&env);
	destroy_mutex(&env);
	return (0);
}
