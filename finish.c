/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 19:45:08 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/27 19:45:51 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_memory(void *ptr, t_phil *philos)
{
	int		i;
	t_list	*vl;

	vl = (t_list *)ptr;
	i = 0;
	pthread_mutex_lock(&vl->print_mutex);
	while (i < vl->n)
		pthread_mutex_destroy(&(vl->fork_mutex[i++]));
	free(vl->lasteats);
	free(vl->forks);
	free(vl->fork_mutex);
	free(philos);
	pthread_mutex_unlock(&vl->print_mutex);
	pthread_mutex_destroy(&vl->print_mutex);
}

int	stop_join(void *ptr, t_phil *philos)
{
	t_list	*vl;

	vl = (t_list *)ptr;
	vl->i = 0;
	while (vl->i < vl->n)
	{
		if (pthread_join(philos[vl->i].thread, NULL))
			return (1);
		vl->i++;
	}
	pthread_mutex_lock(&vl->print_mutex);
	vl->rip_checker_stop = 1;
	pthread_mutex_unlock(&vl->print_mutex);
	if (pthread_join(vl->ripchecker_th, NULL))
		return (1);
	return (0);
}
