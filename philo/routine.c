/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/16 11:48:10 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

	//tenir en compte els temps de parametres si son compatibles. Dormir + menjar no pot donar mort. Tenir en compte tambe pel temps q han de passar pensant.
	//no se si hauria de retornar alguna cosa amb mes sentit?
	//check for died philosophers inside the while?
	//quina es la millor manera de keep track of time after last_meal? crear un altre subthread que sigui el comptador de mort, que si arriba a x amb menjar a 0 mori?
//UN COP UN ESTA ESCRIT QUE MOR, QUE NO S'ESCRIGUI RES MES!!!
//anar checking el temps que no es morin
//prioritzar d'alguna manera els que fa mes que no mengen (si el temps entre l-ultim meal i lactual es mes gran que el de menjar, que comenci a demanar ja la forquilla!!!) -> utilitzar un mutex d'urgencia de la relacio de vegades q fa que tu no menges respecte el que ha menjat mes vegades o anar progressant per mutexs durgencia i usleep en cadascun una estona segns els temps en general
//TORNAR A POSAR ROLS SI POT APORTAR ALGUNA COSA
void	*routine(void *arg)
{
	int			x_feed;
	t_env		*env;
	int			philo_id;
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo_id = (int)philo->id;
	env = (t_env *)philo->env;
	x_feed = 0;
	if (philo_id % 2 == 0)
		thinking(env, philo_id, env->time_eat);
	else if (philo_id == env->num_philo && philo_id != 1)
		thinking(env, philo_id, 2 * env->time_eat);
	while (!is_finished(env))
	{
		eating(env, philo_id);
		if (++x_feed == env->x_eat)
			increase_fed_philo(env);
		sleeping(env, philo_id);
		thinking(env, philo_id, (float) 0.9 * (env->time_die - env->time_eat - env->time_sleep));
	}
	return (arg);
}

//incloure variable d-urgencia?? o nomes tindria sentit en el bonus?!
//PROBLEMA si es queda bloquejat aqui perque esta ocupada la forquilla o perque no existeix si nomes nhi ha un, pot morir aqui i que no me nenteri amb menys de 10ms!?!?
//print when it has taken just one or both forks??
void	eating(t_env *env, int philo_id)
{
	long long	current_meal;

	pthread_mutex_lock(&env->fork[philo_id - 1]);
	if (!is_finished(env))
		printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
	if (env->num_philo != 1)
		pthread_mutex_lock(&env->fork[philo_id % env->num_philo]);
	else
		ft_msleep(env->time_die);
	current_meal = get_time_msec() - env->start_time;
	update_last_meal(env, philo_id, current_meal);
	if (!is_finished(env))
	{
		printf("%lld %i is eating\n", current_meal, philo_id);
		ft_msleep(env->time_eat);
	}
	pthread_mutex_unlock(&env->fork[philo_id - 1]);
	pthread_mutex_unlock(&env->fork[philo_id % env->num_philo]);
}

void	sleeping(t_env *env, int philo_id)
{
	if (!is_finished(env))
	{
		printf("%lld %i is sleeping\n", get_time_msec() - env->start_time, philo_id);
		ft_msleep(env->time_sleep);
	}
}

void	thinking(t_env *env, int philo_id, long long time)
{
	if (!is_finished(env) && time >= 0)
	{
		printf("%lld %i is thinking\n", get_time_msec() - env->start_time, philo_id);
		ft_msleep(time);
	}
}

void	increase_fed_philo(t_env *env)
{
	pthread_mutex_lock(&env->status_mutex);
	env->fed_philo++;
	pthread_mutex_unlock(&env->status_mutex);
}

void	update_last_meal(t_env *env, int philo_id, long long time)
{
	pthread_mutex_lock(&env->last_meal_mutex[philo_id - 1]);
	env->last_meal[philo_id - 1] = time;
	pthread_mutex_unlock(&env->last_meal_mutex[philo_id - 1]);
}
