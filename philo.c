/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:51:16 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/27 19:45:30 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_phil		*philos;
	t_list		vlist;

	if ((write_args(argc, argv, &vlist) != 0) || (init_main(&vlist) != 0))
		return (EXIT_FAILURE);
	if (pthread_create(&(vlist.ripchecker_th), NULL, &p_ripchecker, &vlist))
		return (EXIT_FAILURE);
	philos = (t_phil *)malloc(sizeof(t_phil) * vlist.n);
	if (!philos)
		return (EXIT_FAILURE);
	vlist.i = 0;
	while (vlist.i < vlist.n)
	{
		pthread_mutex_init(&(vlist.fork_mutex[vlist.i]), NULL);
		philos[vlist.i].lptr = &vlist;
		philos[vlist.i].num = vlist.i;
		philos[vlist.i].iter = 0;
		if (pthread_create(&philos[vlist.i].thread,
				NULL, &p_routine, &philos[vlist.i]))
			return (EXIT_FAILURE);
		vlist.i++;
	}
	stop_join(&vlist, philos);
	clear_memory(&vlist, philos);
	return (0);
}
