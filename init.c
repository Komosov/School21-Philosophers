/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:21:06 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:51:23 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	second_init(void *ptr)
{
	t_list	*vl;

	vl = (t_list *)ptr;
	vl->rip = 0;
	vl->rip_checker_stop = 0;
	vl->iters_done = 0;
	vl->i = 0;
	while (vl->i < vl->n)
	{
		vl->forks[vl->i] = -1;
		vl->lasteats[vl->i++] = NULL;
	}
	gettimeofday(&vl->start, NULL);
}

int	init_main(void *ptr)
{
	t_list	*vl;

	vl = (t_list *)ptr;
	vl->fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vl->n);
	if (!vl->fork_mutex)
		return (1);
	vl->forks = (int *)malloc(sizeof(int) * vl->n);
	if (!vl->forks)
	{
		free(vl->fork_mutex);
		return (1);
	}
	vl->lasteats = (void *)malloc(sizeof(&ptr) * vl->n);
	if (!vl->lasteats)
	{
		free(vl->fork_mutex);
		free(vl->forks);
		return (1);
	}
	pthread_mutex_init(&vl->print_mutex, NULL);
	second_init(ptr);
	return (0);
}
