/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:26:19 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/17 16:12:13 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	increase_fed_philo(t_env *env)
{
	pthread_mutex_lock(&env->status_mutex);
	env->fed_philo++;
	pthread_mutex_unlock(&env->status_mutex);
}

void	update_last_meal(t_env *env, int philo_id, int time)
{
	pthread_mutex_lock(&env->last_meal_mutex[philo_id - 1]);
	env->last_meal[philo_id - 1] = time;
	pthread_mutex_unlock(&env->last_meal_mutex[philo_id - 1]);
}

int	get_last_meal(t_env *env, int philo_id)
{
	int	time;

	pthread_mutex_lock(&env->last_meal_mutex[philo_id - 1]);
	time = env->last_meal[philo_id - 1];
	pthread_mutex_unlock(&env->last_meal_mutex[philo_id - 1]);
	return (time);
}
