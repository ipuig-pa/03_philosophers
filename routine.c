/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:02:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/03 19:16:49 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

routine(t_env *env, int philo_id)
{
	eat(&env, philo_id);
	sleep(&env, philo_id);
	think(&env, philo_id);
}

eat(t_env *env, int philo_id)
{
	//take fork i block mutex
	//mantenir recompte de vegades que menja per comparar amb x_eat i parar si cal quan sigui igual, i diferent a 0 (o posar-lo inicialment a negatiu per distingir quan es el valor inicial??)
	getdayhour... obtenir nom del filo etc 
	printf("%s")
	usleep(time_eat);
}

sleep(t_env *env, int philo_id)
{
	usleep(time_sleep);
}

think(t_env *env, int philo_id)
{
	//com a maxim ha d'aguantar time_die;
}