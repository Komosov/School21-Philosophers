/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_rip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 18:20:05 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 18:21:23 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	rip_processing(void *ptr)
{
	struct timeval	*time_ptr;
	t_list			*vl;

	vl = (t_list *)ptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->lasteats[vl->rci] != NULL)
	{
		time_ptr = vl->lasteats[vl->rci];
		if ((vl->rip_checker_stop == 0)
			&& (ttr(time_ptr->tv_sec, time_ptr->tv_usec, vl->ttl) < 0))
		{
			vl->rip = 1;
			printf("%d \t%d dead\n",
				now_time(vl->start.tv_sec, vl->start.tv_usec), vl->rci + 1);
			pthread_mutex_unlock(&vl->print_mutex);
			return (1);
		}
		if (vl->rip_checker_stop != 0)
		{
			pthread_mutex_unlock(&vl->print_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&vl->print_mutex);
	return (0);
}

void	*p_ripchecker(void *ptr)
{
	t_list	*vl;

	vl = (t_list *)ptr;
	pthread_mutex_lock(&vl->print_mutex);
	while ((vl->rip == 0) && (vl->rip_checker_stop == 0))
	{
		pthread_mutex_unlock(&vl->print_mutex);
		vl->rci = 0;
		pthread_mutex_lock(&vl->print_mutex);
		while ((vl->rci < vl->n) && (vl->rip_checker_stop == 0))
		{
			pthread_mutex_unlock(&vl->print_mutex);
			if (rip_processing(ptr) != 0)
			{
				return (NULL);
			}
			vl->rci++;
			usleep(100);
			pthread_mutex_lock(&vl->print_mutex);
		}
	}
	pthread_mutex_unlock(&vl->print_mutex);
	return (NULL);
}
