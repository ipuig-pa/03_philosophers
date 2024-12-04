/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:31:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/04 15:42:00 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_msec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_value(char *str)
{
	long long	value;

	value = 0;
	//no se si es necessari aquesta part de treure espais de davant i de darrere
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		integer = integer * 10 + (*str - '0');
		str++;
	}
	//no se si es necessari aquesta part de treure espais de davant i de darrere
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (str != '\0')
		return (-1);
	return (value);
}
