/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/14 17:25:37 by ipuig-pa         ###   ########.fr       */
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

	env = (t_env *)arg;
	philo_id = env->philo_id;
	x_feed = 0;
	update_last_meal(env, philo_id, env->start_time);
	if (philo_id % 2 == 0) //&& x_feed == 0 && !is_finished(env)
		thinking(env, philo_id, env->time_eat);
	else if (philo_id == env->num_philo && philo_id != 1) //&& x_feed == 0 && !is_finished(env)
		thinking(env, philo_id, 2 * env->time_eat);
	while (!is_finished(env))
	{
		eating(env, philo_id);
		if (++x_feed == env->x_eat)
			increase_fed_philo(env);
		sleeping(env, philo_id);
		thinking(env, philo_id, (float) 0.5 * (env->time_die - env->time_eat - env->time_sleep));
	}
	return (NULL);
}

//incloure variable d-urgencia?? o nomes tindria sentit en el bonus?!
//PROBLEMA si es queda bloquejat aqui perque esta ocupada la forquilla o perque no existeix si nomes nhi ha un, pot morir aqui i que no me nenteri amb menys de 10ms!?!?
//print when it has taken just one or both forks??
void	eating(t_env *env, int philo_id)
{
	long long	current_meal;

	if (get_time_msec() - get_last_meal(env, philo_id) > env->time_die)
		die(env, philo_id);
	pthread_mutex_lock(&env->fork[philo_id - 1]);
	if (!is_finished(env))
		printf("%lld %i has taken a fork\n", get_time_msec() - env->start_time, philo_id);
	if (env->num_philo != 1)
		pthread_mutex_lock(&env->fork[philo_id % env->num_philo]);
	else
	{
		ft_usleep(env->time_die);
		die(env, philo_id);
	}
	current_meal = get_time_msec() - env->start_time;
	if (current_meal - get_last_meal(env, philo_id) > env->time_die)
		die(env, philo_id);
	update_last_meal(env, philo_id, current_meal);
	if (!is_finished(env))
	{
		printf("%lld %i is eating\n", current_meal, philo_id);
		ft_usleep(env->time_eat);
	}
	pthread_mutex_unlock(&env->fork[philo_id - 1]);
	pthread_mutex_unlock(&env->fork[philo_id % env->num_philo]);
}

void	sleeping(t_env *env, int philo_id)
{
	if (!is_finished(env))
		printf("%lld %i is sleeping\n", get_time_msec() - env->start_time, philo_id);
	if (env->time_die < env->time_sleep)
	{
		ft_usleep(env->time_die);
		die(env, philo_id);
	}
	else
		ft_usleep(env->time_sleep);
}

void	thinking(t_env *env, int philo_id, long long time)
{
	if (!is_finished(env) && time != 0)
	{
		printf("%lld %i is thinking\n", get_time_msec() - env->start_time, philo_id);
		ft_usleep(time );
	}
}

// qu[e fer quan die??? com parar la simulacio?!?]
void	die(t_env *env, int philo_id)
{
	if (!is_finished(env))
	{
		pthread_mutex_lock(&env->status_mutex);
		env->dead_philo++;
		printf("%lld %i died\n", get_time_msec() - env->start_time, philo_id);
		pthread_mutex_unlock(&env->status_mutex);
	}
}

	//check aqui tambe si han passat mes min de l-ultim meal? podria afegir un array a l-estructura mb el last meal de cadascun, o be afegir-lo aqui com a variable
	//printf("%i\n", env->dead_philo);
int	is_finished(t_env *env)
{
	int	finished;

	pthread_mutex_lock(&env->status_mutex);
	finished = env->dead_philo > 0 || env->fed_philo == env->num_philo;
	pthread_mutex_unlock(&env->status_mutex);
	return (finished);
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

long long	get_last_meal(t_env *env, int philo_id)
{
	long long	time;

	pthread_mutex_lock(&env->last_meal_mutex[philo_id - 1]);
	time = env->last_meal[philo_id - 1];
	pthread_mutex_unlock(&env->last_meal_mutex[philo_id - 1]);
	return (time);
}
