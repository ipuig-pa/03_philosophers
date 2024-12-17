/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:31:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/16 11:48:57 by ipuig-pa         ###   ########.fr       */
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
		value = value * 10 + (*str - '0');
		str++;
	}
	//no se si es necessari aquesta part de treure espais de davant i de darrere
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str != '\0')
		return (-1);
	return (value);
}

int	ft_msleep(long long time)
{
	long long	start;

	start = get_time_msec();
	while (get_time_msec() - start >= time)
		usleep(500);
	return (0);
}
