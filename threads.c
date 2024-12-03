/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:04:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/03 19:12:31 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

pthread_t	create_thread(t_env *env)
{
	pthread_t	philo;

//no se ben be si hauria de fer return o no, i tampoc se si he de fer algun check que el pthread create ha anat be com si fos malloc
	return (pthread_create(&philo, NULL, &routine, env));
}
