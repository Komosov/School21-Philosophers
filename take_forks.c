/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:06:01 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/28 20:06:34 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork_1(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip == 0)
	{
		vl->forks[p->fork_1] = p->num;
		printf("%d \t%d has taken a fork 1\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		pthread_mutex_unlock(&vl->print_mutex);
	}
	else
	{
		pthread_mutex_unlock(&vl->print_mutex);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
		return (1);
	}
	return (0);
}

static int	take_fork_2(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip == 0)
	{
		vl->forks[p->fork_2] = p->num;
		printf("%d \t%d has taken a fork 2\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		pthread_mutex_unlock(&vl->print_mutex);
	}
	else
	{
		pthread_mutex_unlock(&vl->print_mutex);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_2]);
		return (1);
	}
	return (0);
}

static void	first_fork_lock(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip == 0)
	{
		pthread_mutex_unlock(&vl->print_mutex);
		pthread_mutex_lock(&vl->fork_mutex[p->fork_1]);
	}
	else
		pthread_mutex_unlock(&vl->print_mutex);
}

static void	second_fork_lock(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	if (vl->rip == 0)
	{
		pthread_mutex_unlock(&vl->print_mutex);
		pthread_mutex_lock(&vl->fork_mutex[p->fork_2]);
	}
	else
	{
		pthread_mutex_unlock(&vl->print_mutex);
		pthread_mutex_unlock(&vl->fork_mutex[p->fork_1]);
	}
}

int	p_take_forks(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	first_fork_lock(p);
	if (is_rip_after_mutex_1(p) == 1)
		return (0);
	else
		if (take_fork_1(p) == 1)
			return (0);
	check_only_one_fork(p);
	second_fork_lock(p);
	if (is_rip_after_mutex_2(p) == 1)
		return (0);
	else
		if (take_fork_2(p) == 1)
			return (0);
	return (0);
}
