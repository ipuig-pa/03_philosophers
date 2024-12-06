/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/06 18:32:54 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	int			x_feed;
	t_env		*env;
	int			philo_id;
	int			role;

	env = (t_env *)arg;
	philo_id = env->philo_id;
	role = philo_id - 1;
	x_feed = 0;
	env->last_meal[philo_id - 1] = env->start_time;
	while (!is_finished(env))
	{
		if (role % 2 != 0 && x_feed == 0 && !is_finished(env))
			thinking(env, philo_id, env->time_eat);
		else if (role % 2 != 0 && !is_finished(env))
			thinking(env, philo_id, env->time_eat - env->time_sleep);
		else if (role % 2 == 0 && role == (env->num_philo - 1) && role != 0 && x_feed == 0 && !is_finished(env))
			thinking(env, philo_id, 2 * env->time_eat);
		else if (role % 2 == 0 && role == (env->num_philo - 1) && role != 0 && !is_finished(env))
			thinking(env, philo_id, 2 * env->time_eat - env->time_sleep);
		else if (!is_finished(env))
		{
			env->last_meal[philo_id - 1] = eating(env, philo_id);
			x_feed++;
			if (x_feed == env->x_eat)
				env->fed_philo++;
			if (env->dead_philo == 0 && env->fed_philo != env->num_philo)
				sleeping(env, philo_id);
		}
		role = (role - 1 + env->num_philo) % env->num_philo;
	}
	//PROBLEMA quan nomes hi ha 1 o 2 philo
	//tenir en compte els temps de parametres si son compatibles. Dormir + menjar no pot donar mort. Tenir en compte tambe pel temps q han de passar pensant.
	//no se si hauria de retornar alguna cosa amb mes sentit?
	return (NULL);
	//check for died philosophers inside the while?
	//quina es la millor manera de keep track of time after last_meal? crear un altre subthread que sigui el comptador de mort, que si arriba a x amb menjar a 0 mori?
}

//UN COP UN ESTA ESCRIT QUE MOR, QUE NO S'ESCRIGUI RES MES!!!
//anar checking el temps que no es morin
//prioritzar d'alguna manera els que fa mes que no mengen (si el temps entre l-ultim meal i lactual es mes gran que el de menjar, que comenci a demanar ja la forquilla!!!)

long long	eating(t_env *env, int philo_id)
{
	long long	current_meal;

	//incloure variable d-urgencia?? o nomes tindria sentit en el bonus?!
	//PROBLEMA si es queda bloquejat aqui perque esta ocupada la forquilla o perque no existeix si nomes nhi ha un, pot morir aqui i que no me nenteri amb menys de 10ms!?!?

	if ((get_time_msec() - env->start_time - env->last_meal[philo_id - 1]) > env->time_die && !is_finished(env))
		die(env, philo_id);
	//SEGUIR PER AQUI!!! posar aqui el thinking en lloc de a dalt segons el temps que quedi per morir???
	if (!is_finished(env))
		pthread_mutex_lock(&env->fork[philo_id - 1]);
		printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
	if (env->num_philo != 1)
		pthread_mutex_lock(&env->fork[philo_id % env->num_philo]);
	else 
	{
		usleep(env->time_die * 1000);
		die(env, philo_id);
	}
	//print when it has taken just one or both forks??
	current_meal = get_time_msec() - env->start_time;
	if ((current_meal - env->last_meal[philo_id - 1]) > env->time_die && !is_finished(env))
		die(env, philo_id);
	if (!is_finished(env))
	{
		printf("%lld %i is eating\n", current_meal, philo_id);
		usleep(env->time_eat * 1000);
	}
	pthread_mutex_unlock(&env->fork[philo_id - 1]);
	pthread_mutex_unlock(&env->fork[philo_id % env->num_philo]);
	return (current_meal);
}

void	sleeping(t_env *env, int philo_id)
{
	if (!is_finished(env))
		printf("%lld %i is sleeping\n", get_time_msec() - env->start_time, philo_id);
	if (env->time_die < env->time_sleep)
	{
		usleep(env->time_die * 1000);
		die(env, philo_id);
	}
	else
		usleep(env->time_sleep * 1000);
}

void	thinking(t_env *env, int philo_id, long long time)
{
	if (time != 0 && !is_finished(env))
	{
		printf("%lld %i is thinking\n", get_time_msec() - env->start_time, philo_id);
		usleep(time * 1000);
	}
}

void	die(t_env *env, int philo_id)
{
	if (!is_finished(env))
	{
		printf("%lld %i died\n", get_time_msec() - env->start_time, philo_id);
		env->dead_philo++;
	}
	// qu[e fer quan die??? com parar la simulacio?!?]
}

int	is_finished(t_env *env)
{
	//check aqui tambe si han passat mes min de l-ultim meal? podria afegir un array a l-estructura mb el last meal de cadascun, o be afegir-lo aqui com a variable
	if (env->dead_philo == 0 && env->fed_philo != env->num_philo)
		return (0);
	return (1);
}
