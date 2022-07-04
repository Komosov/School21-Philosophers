/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:14:22 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/28 12:59:23 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arg_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			printf("Error! Bad argument: %s\n", arg);
			printf("Only digits possible. Example:\n");
			printf("./philo 5 800 200 200\n");
			printf("./philo 5 800 200 200 7\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	args_check(int argc, char **argv)
{
	int	i;

	if ((argc < 5) || (argc > 6))
	{
		printf("Error! Wrong arguments number! Example:\n");
		printf("./philo 5 800 200 200\n");
		printf("./philo 5 800 200 200 7\n");
		return (1);
	}
	i = 1;
	while (i < argc)
		if (arg_check(argv[i++]) != 0)
			return (1);
	return (0);
}

int	write_args(int argc, char **argv, void *ptr)
{
	t_list	*vl;

	if (args_check(argc, argv) != 0)
		return (1);
	vl = (t_list *)ptr;
	vl->n = ft_atoi(argv[1]);
	vl->ttl = ft_atoi(argv[2]);
	vl->tte = ft_atoi(argv[3]);
	vl->tts = ft_atoi(argv[4]);
	if (argc == 6)
		vl->iters = ft_atoi(argv[5]);
	else
		vl->iters = INT_MAX;
	return (0);
}
