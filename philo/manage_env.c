/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:23:06 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:49:39 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_env(t_env *env, int argc, char **argv)
{
	env->num_philo = (int)get_valid_value(argv[1]);
	env->time_die = get_valid_value(argv[2]);
	env->time_eat = get_valid_value(argv[3]);
	env->time_sleep = get_valid_value(argv[4]);
	if (argc == 6)
		env->x_eat = (int)get_valid_value(argv[5]);
}

int	get_valid_value(char *str)
{
	int	value;

	value = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != '\0' || value == 0)
		return (0);
	return (value);
}

void	final_free(t_env *env)
{
	if (env->philo)
		free(env->philo);
	if (env->last_meal)
		free(env->last_meal);
	destroy_mutex(env);
}
