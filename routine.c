/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:09:12 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 18:21:18 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	iterations_limit(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&vl->print_mutex);
	vl->iters_done++;
	printf("%d \t%d is reached \"%d\" iterations.\n",
		now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1, vl->iters);
	if (vl->iters_done == vl->n)
		vl->rip = 1;
	pthread_mutex_unlock(&vl->print_mutex);
}

static void	init_routine(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	gettimeofday(&p->last_eat, NULL);
	pthread_mutex_lock(&vl->print_mutex);
	vl->lasteats[p->num] = &p->last_eat;
	pthread_mutex_unlock(&vl->print_mutex);
	if (p->num % 2 != 0)
		ft_usleep(vl->tte / 2 * 1000, ptr);
	p->fork_1 = ft_min(p->num, ((p->num + 1) % vl->n));
	p->fork_2 = ft_max(p->num, ((p->num + 1) % vl->n));
}

static void	iters_count(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	p->iter++;
	if (p->iter == INT_MAX)
		p->iter = 0;
	if (p->iter == vl->iters)
		iterations_limit(ptr);
}

void	*p_routine(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	init_routine(ptr);
	while (1)
	{
		p_take_forks(ptr);
		p_eat(ptr);
		p_put_forks(ptr);
		iters_count(ptr);
		p_sleep(ptr);
		p_think(ptr);
		pthread_mutex_lock(&vl->print_mutex);
		if (vl->rip == 1)
		{
			pthread_mutex_unlock(&vl->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&vl->print_mutex);
	}
	return (NULL);
}
