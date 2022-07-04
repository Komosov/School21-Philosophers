/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:01:02 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/28 12:58:05 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	now_time(long sec, int msec)
{
	struct timeval	now;
	struct timeval	dtv;

	gettimeofday(&now, NULL);
	dtv.tv_sec = now.tv_sec - sec;
	dtv.tv_usec = now.tv_usec - msec;
	if (dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

int	now_time_usec(long sec, int msec)
{
	struct timeval	now;
	struct timeval	dtv;

	gettimeofday(&now, NULL);
	dtv.tv_sec = now.tv_sec - sec;
	dtv.tv_usec = now.tv_usec - msec;
	if (dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	return (dtv.tv_sec * 1000000 + dtv.tv_usec);
}

long	ttr(long sec, int usec, int ttl)
{
	struct timeval	now;
	struct timeval	dtv;

	gettimeofday(&now, NULL);
	dtv.tv_sec = now.tv_sec - sec;
	dtv.tv_usec = now.tv_usec - usec;
	if (dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	return (ttl - (dtv.tv_sec * 1000 + dtv.tv_usec / 1000));
}
