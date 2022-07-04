/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelena <lhelena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:51:27 by lhelena           #+#    #+#             */
/*   Updated: 2022/07/03 17:50:46 by lhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_list
{
	int				i;
	int				n;
	int				rci;
	int				ttl;
	int				tte;
	int				tts;
	int				rip;
	int				iters;
	int				iters_done;
	int				*forks;
	void			**lasteats;
	struct timeval	start;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		ripchecker_th;
	int				rip_checker_stop;
}t_list;

typedef struct s_phil
{
	int				i;
	int				num;
	int				iter;
	int				fork_1;
	int				fork_2;
	void			*lptr;
	pthread_t		thread;
	struct timeval	last_eat;
}t_phil;

void	check_only_one_fork(void *ptr);
void	clear_memory(void *ptr, t_phil *philos);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	ft_usleep(int usec, void *ptr);
int		init_main(void *ptr);
int		is_rip_after_mutex_1(void *ptr);
int		is_rip_after_mutex_2(void *ptr);
int		now_time(long sec, int msec);
int		now_time_usec(long sec, int msec);
int		p_eat(void *ptr);
void	p_put_forks(void *ptr);
void	*p_ripchecker(void *ptr);
void	*p_routine(void *ptr);
void	p_sleep(void *ptr);
int		p_take_forks(void *ptr);
void	p_think(void *ptr);
int		stop_join(void *ptr, t_phil *philos);
long	ttr(long sec, int usec, int ttl);
int		write_args(int argc, char **argv, void *ptr);

#endif
