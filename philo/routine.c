/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/05 21:08:13 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int			x_feed;
	long long	last_meal;
	t_env		*env;
	int			philo_id;

	env = (t_env *)arg;
	philo_id = env->philo_id;
	x_feed = 0;
	last_meal = env->start_time;
	while (env->dead_philo == 0 && env->fed_philo != env->num_philo)
	{
		last_meal = ph_eat(env, philo_id, last_meal);
		x_feed++;
		if (x_feed == env->x_eat)
			env->fed_philo++;
		if (env->dead_philo == 0 && env->fed_philo != env->num_philo)
			ph_sleep(env, philo_id);
		if (env->dead_philo == 0 && env->fed_philo != env->num_philo)
			ph_think(env, philo_id);
	}
	//no se si hauria de retornar alguna cosa amb mes sentit?
	return (NULL);
	//check for died philosophers inside the while?
	//quina es la millor manera de keep track of time after last_meal? crear un altre subthread que sigui el comptador de mort, que si arriba a x amb menjar a 0 mori?
}

long long	ph_eat(t_env *env, int philo_id, long long last_meal)
{
	long long	current_meal;

	//problema si es queda bloquejat aqui perque esta ocupada la forquilla, pot morir aqui i que no me nenteri amb menys de 10ms!?!?
	if (philo_id != 1)
	{
		pthread_mutex_lock(&env->fork[philo_id - 2]);
		printf("fork[%i] locked\n", philo_id - 2);
	}
	pthread_mutex_lock(&env->fork[philo_id - 1]);
	printf("fork[%i] locked\n", philo_id - 1);
	if (philo_id == 1)
	{
		pthread_mutex_lock(&env->fork[env->num_philo - 1]);
		printf("fork[%i] locked\n", env->num_philo - 1);
	}
	// importancia de comprovar com estan els altres d'alguna manera, que no agafi aquest la forquilla abans que el 4
	//print when it has taken just one or both forks??
	printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
	current_meal = get_time_msec() - env->start_time;
	if ((current_meal - last_meal) >= env->time_die)
		ph_die(env, philo_id);
	printf("%lld %i is eating\n", current_meal, philo_id);
	usleep(env->time_eat * 1000);
	pthread_mutex_unlock(&env->fork[philo_id - 1]);
	if (philo_id != 1)
		pthread_mutex_unlock(&env->fork[philo_id - 2]);
	else
		pthread_mutex_unlock(&env->fork[env->num_philo - 1]);
	return (current_meal);
}

void	ph_sleep(t_env *env, int philo_id)
{
	printf("%lld %i is sleeping\n", get_time_msec() - env->start_time, philo_id);
	if (env->time_die < env->time_sleep)
	{
		usleep(env->time_die * 1000);
		ph_die(env, philo_id);
	}
	else
		usleep(env->time_sleep * 1000);
}

void	ph_think(t_env *env, int philo_id)
{
	printf("%lld %i is thinking\n", get_time_msec() - env->start_time, philo_id);
	usleep(100);
}

void	ph_die(t_env *env, int philo_id)
{
	printf("%lld %i died\n", get_time_msec() - env->start_time, philo_id);
	env->dead_philo++;
	// qu[e fer quan die??? com parar la simulacio?!?]
}
