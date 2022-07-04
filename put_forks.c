/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:19:47 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/28 20:05:26 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_put_forks(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip == 0)
	{
		vl->forks[p->fork_2] = -1;
		vl->forks[p->fork_1] = -1;
	}
	pthread_mutex_unlock(&vl->print_mutex);
	pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
	pthread_mutex_unlock(&vl->fork_mutex[p->fork_2]);
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < 0)
	{
		pthread_mutex_lock(&vl->print_mutex);
		if (vl->rip == 0)
		{
			vl->rip = 1;
			printf("%d \t%d dead\n",
				now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		}
		pthread_mutex_unlock(&vl->print_mutex);
	}
}
