/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 23:21:38 by lhelena           #+#    #+#             */
/*   Updated: 2022/06/26 19:02:22 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	atoi_first_digit(const char *str)
{
	int	i;
	int	start;
	int	dc;

	i = 0;
	start = 0;
	dc = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	while ((str[i] == '+') || (str[i] == '-'))
		i++;
	start = i;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		dc++;
		i++;
	}
	if (0 == dc)
		return (-1);
	return (start);
}

static int	atoi_last_digit(const char *str)
{
	int	i;
	int	start;
	int	dc;

	i = 0;
	start = 0;
	dc = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	while ((str[i] == '+') || (str[i] == '-'))
		i++;
	start = i;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		dc++;
		i++;
	}
	if (0 == dc)
		return (-1);
	return (i - 1);
}

static long	atoi_minus_search(const char *str)
{
	int	i;
	int	dc;
	int	mc;

	i = 0;
	dc = 0;
	mc = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	while ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			mc++;
		i++;
		dc++;
	}
	if (dc > 1)
		return (0);
	else if (1 == mc)
		return (-1);
	else
		return (1);
}

static int	atoi_overlimit_check(const char *str)
{
	int		start;
	int		stop;
	long	res;
	int		i;

	start = atoi_first_digit(str);
	stop = atoi_last_digit(str);
	res = 0;
	if ((stop - start) > 19)
		return (-1);
	i = start;
	if (((stop - start) == 19) && ((str[i] - '0') == 9))
	{
		i++;
		while (i <= stop)
		{
			res = res * 10 + str[i] - '0';
			i++;
		}
		if (res > 223372036854775807)
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		start;
	int		stop;
	long	res;
	int		i;

	start = atoi_first_digit(str);
	stop = atoi_last_digit(str);
	res = 0;
	if (((-1 == start) || (0 == atoi_minus_search(str)))
		|| (((stop - start) > 18) && (-1 == atoi_minus_search(str))))
		return (0);
	if (-1 == atoi_overlimit_check(str))
		return (-1);
	i = start;
	while (i <= stop)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	res = res * atoi_minus_search(str);
	return (res);
}
