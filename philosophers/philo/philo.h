/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halaqoh <halaqoh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:17:44 by halaqoh           #+#    #+#             */
/*   Updated: 2022/06/04 22:52:17 by halaqoh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct filozof
{
	size_t			nbr_philo;
	size_t			tslep;
	size_t			teat;
	size_t			tdie;
	size_t			*l_eat;
	size_t			*is_die;
	size_t			*is_eating;
	int				nbr_to_eat;
	int				*is_alleat;
	size_t			t0;
	size_t			die;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	roma;
	pthread_mutex_t	pint;
	size_t			nbr_eat;
	size_t			vv;
}t_filozof;

int		ft_atoi(const char *str);
void	init_p(t_filozof **p, char **argv, int argc);
long	tim(void);
int		is_mat(t_filozof *p, size_t	tn);
int		ft_alleat(t_filozof *p);
void	*routine(t_filozof *p);
void	pint(t_filozof *p, int i, char *msg);
void	run(t_filozof *p, int i);
void	ft_usleep(int num);

#endif
