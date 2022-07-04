/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:24:02 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:21:03 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	dead_while_eating(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip != 0)
		pthread_mutex_unlock(&vl->print_mutex);
	else if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < vl->tte)
	{
		pthread_mutex_unlock(&vl->print_mutex);
		ft_usleep(ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) * 1000,
			ptr);
		pthread_mutex_lock(&vl->print_mutex);
		if (vl->rip == 0)
		{
			vl->rip = 1;
			printf("%d \t%d dead\n",
				now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		}
		pthread_mutex_unlock(&vl->print_mutex);
	}
	else
		pthread_mutex_unlock(&vl->print_mutex);
}

static void	eating_time(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip != 0)
		pthread_mutex_unlock(&vl->print_mutex);
	else
	{
		pthread_mutex_unlock(&vl->print_mutex);
		ft_usleep(vl->tte * 1000, ptr);
	}
}

int	p_eat(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	gettimeofday(&p->last_eat, NULL);
	if (vl->rip == 0)
		printf("%d \t%d is eating\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	pthread_mutex_unlock(&vl->print_mutex);
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < vl->tte)
		dead_while_eating(p);
	else
		eating_time(p);
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip != 0)
	{
		pthread_mutex_unlock(&vl->print_mutex);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_2]);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
	}
	else
		pthread_mutex_unlock(&vl->print_mutex);
	return (0);
}
