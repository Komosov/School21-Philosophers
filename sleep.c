/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:25:34 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 14:23:41 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_sleep(void *ptr)
{
	t_list	*vl;
	t_phil	*p;

	p = (t_phil *)ptr;
	vl = (t_list *)p->lptr;
	pthread_mutex_lock(&(vl->print_mutex));
	if (vl->rip == 0)
		printf("%d \t%d is sleeping\n",
			now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
	pthread_mutex_unlock(&(vl->print_mutex));
	if (ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl) < vl->tts)
	{
		ft_usleep(ttr(p->last_eat.tv_sec, p->last_eat.tv_usec, vl->ttl)
			* 1000, ptr);
		pthread_mutex_lock(&(vl->print_mutex));
		if (vl->rip == 0)
		{
			vl->rip = 1;
			printf("%d \t%d dead\n",
				now_time(vl->start.tv_sec, vl->start.tv_usec), p->num + 1);
		}
		pthread_mutex_unlock(&(vl->print_mutex));
	}
	else
		ft_usleep(vl->tts * 1000, ptr);
}
