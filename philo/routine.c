/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/13 18:05:01 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//RACE CONDITIONS!?!?!? ATOMIC ACTIONS

	//tenir en compte els temps de parametres si son compatibles. Dormir + menjar no pot donar mort. Tenir en compte tambe pel temps q han de passar pensant.
	//no se si hauria de retornar alguna cosa amb mes sentit?
	//check for died philosophers inside the while?
	//quina es la millor manera de keep track of time after last_meal? crear un altre subthread que sigui el comptador de mort, que si arriba a x amb menjar a 0 mori?
//UN COP UN ESTA ESCRIT QUE MOR, QUE NO S'ESCRIGUI RES MES!!!
//anar checking el temps que no es morin
//prioritzar d'alguna manera els que fa mes que no mengen (si el temps entre l-ultim meal i lactual es mes gran que el de menjar, que comenci a demanar ja la forquilla!!!)
//TREURE ROLS SI NO ELS UTILITZO
void	*routine(void *arg)
{
	int			x_feed;
	t_env		*env;
	int			philo_id;

	env = (t_env *)arg;
	philo_id = env->philo_id;
	x_feed = 0;
	env->last_meal[philo_id - 1] = env->start_time;
	if (philo_id % 2 == 0) //&& x_feed == 0 && !is_finished(env, philo_id)
		thinking(env, philo_id, env->time_eat);
	else if (philo_id == env->num_philo) //&& x_feed == 0 && !is_finished(env, philo_id)
		thinking(env, philo_id, 2 * env->time_eat);
	while (!is_finished(env, philo_id))
	{
		env->last_meal[philo_id - 1] = eating(env, philo_id);
		if (++x_feed == env->x_eat)
			env->fed_philo++;
		sleeping(env, philo_id);
		thinking(env, philo_id, (float) 0.8 * (env->time_die - env->time_eat - env->time_sleep));
	}
	return (NULL);
}

//incloure variable d-urgencia?? o nomes tindria sentit en el bonus?!
//PROBLEMA si es queda bloquejat aqui perque esta ocupada la forquilla o perque no existeix si nomes nhi ha un, pot morir aqui i que no me nenteri amb menys de 10ms!?!?
//print when it has taken just one or both forks??
long long	eating(t_env *env, int philo_id)
{
	long long	current_meal;

	pthread_mutex_lock(&env->fork[philo_id - 1]);
	if (!is_finished(env, philo_id))
		printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
	if (env->num_philo != 1)
		pthread_mutex_lock(&env->fork[philo_id % env->num_philo]);
	else
	{
		usleep(env->time_die * 1000);
		die(env, philo_id);
	}
	current_meal = get_time_msec() - env->start_time;
	if ((current_meal - env->last_meal[philo_id - 1]) > env->time_die && !is_finished(env, philo_id))
		die(env, philo_id);
	if (!is_finished(env, philo_id))
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
	if (!is_finished(env, philo_id))
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
	if (!is_finished(env, philo_id))
	{
		printf("%lld %i is thinking\n", get_time_msec() - env->start_time, philo_id);
		usleep(time * 1000);
	}
}

// qu[e fer quan die??? com parar la simulacio?!?]
void	die(t_env *env, int philo_id)
{
	if (!is_finished(env, philo_id))
	{
		env->dead_philo++;
		printf("%lld %i died\n", get_time_msec() - env->start_time, philo_id);
	}
}

	//check aqui tambe si han passat mes min de l-ultim meal? podria afegir un array a l-estructura mb el last meal de cadascun, o be afegir-lo aqui com a variable
	//printf("%i\n", env->dead_philo);
int	is_finished(t_env *env, int philo_id)
{
	if ((get_time_msec() - env->start_time - env->last_meal[philo_id - 1]) > env->time_die)
		die(env, philo_id);
	if (env->dead_philo == 0 && env->fed_philo != env->num_philo)
		return (0);
	return (1);
}
