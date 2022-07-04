/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:06:01 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/28 20:06:24 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_rip_after_mutex_1(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
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
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
		return (1);
	}
	else
		return (0);
}

int	is_rip_after_mutex_2(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
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
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_2]);
		return (1);
	}
	return (0);
}

void	check_only_one_fork(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (p->num == ((p->num + 1) % vl->n))
	{
		pthread_mutex_unlock(&vl->print_mutex);
		ft_usleep(vl->ttl * 1000, p);
		pthread_mutex_lock(&vl->print_mutex);
		vl->rip = 1;
		printf("%d \t%d dead\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
	}
	pthread_mutex_unlock(&vl->print_mutex);
}
