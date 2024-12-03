/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:21:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/03 19:11:15 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_env			env;
	pthread_mutex_t	*fork;
	int				i;
	pthread_t		*philo;

	if (argc < 5 || argc > 6)
		return (wirte(2, "Incorrect number of arguments\n", 31), 1);
	memset(&env, 0, sizeof(t_env));
	env.num_philo = argv[1];
	env.time_die = argv[2];
	env.time_eat = argv[3];
	env.time_sleep = arg[4];
	if (argc == 6)
		env.x_eat = argv[5];
	i = 0;
	while (i < num_philo)
	{
		philo[i] = create_thread(&env);
		i++;
	}
//no se en quin moment els he d'unir


	fork = malloc(sizeof(argv[]));
	f = 0;
	while (f < env.num_philo)
	{
		pthread_mutex_init(&fork[f], NULL);
	}

}
